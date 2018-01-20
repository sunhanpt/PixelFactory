#pragma once;

#include <string>
#include <vector>
#include <hash_map>
#include <map>
#include <Windows.h>

#define AFPCK_VERSION		0x00020003
#define MAX_PATH			512

typedef __int64				aptrint;
typedef unsigned __int64	auptrint;

class afilepack_mem_man
{
public:
	enum
	{
		mem_block_size = 1024 * 1024,
	};

	afilepack_mem_man()
	{
		cur_block = nullptr;
		cur_used = 0;
	}

	~afilepack_mem_man()
	{
		clear();
	}

	void clear()
	{
		for (size_t i = 0; i < blocks.size(); i++) {
			delete[] blocks[i];
		}

		blocks.clear();
		cur_block = nullptr;
		cur_used = 0;
	}

	void * allocate(size_t size)
	{
		if (size >= mem_block_size)
		{
			BYTE* p = new BYTE[size];
			blocks.push_back(p);
			return p;
		}
		else if (size + cur_used > mem_block_size || cur_block == 0)
		{
			BYTE* p = new BYTE[mem_block_size];
			cur_block = p;
			blocks.push_back(p);
			cur_used = size;
			return p;
		}
		else
		{
			BYTE * p = cur_block + cur_used;
			cur_used += size;
			return p;
		}
	}

protected:

	std::vector<BYTE*> blocks;
	BYTE* cur_block;
	size_t cur_used;

};

class AFilePackage
{
public:
	class entry
	{
	public:
		char* _name;
		entry() :_name(NULL) {}
		entry(const char* name) { _name = new char[strlen(name) + 1]; strcpy(_name, name); }
		virtual ~entry() { delete[] _name; }
		virtual bool isContainer() = 0;
		virtual int GetIndex() = 0;
		virtual entry* SearchItem(const char*) = 0;
		virtual bool CanDoDel() { return false; }
		virtual void Release()
		{
			if (CanDoDel())
				delete[] _name;
			_name = 0;
		}
	};

	class directory : public entry
	{
		std::vector<entry *> _list;
		int searchItemIndex(const char* name, int * pos);
	public:
		directory(const char * name) :entry(name) {}
		directory() {}
		~directory() {}
		int clear();
		virtual bool IsContainer() { return true; }
		virtual int GetIndex() { return -1; }
		virtual entry* SearchItem(const char*);
	public:
		entry* GetItem(int index);
		int GetEntryCount() { return _list.size(); }
		entry* GetEntry(int i) { return _list[i]; }
		int RemoveItem(const char* name);
		int AppendEntry(entry *);
		int SearchEntry(const char * filename);
	};

	class file : public entry
	{
		int _index;
	public:
		file() {};
		~file() { Release(); }
		file(const char * name, int index) : entry(name), _index(index) {}
		virtual bool IsContainer() { return false; }
		virtual entry* SearchItem(const char*) { return NULL; }
		virtual int GetIndex() { return _index; }
		void SetIndex(int index) { _index = index; }
		virtual bool CanDoDel();
		void SetName(const char* name);
	};

public:

	enum OPENMODE
	{
		OPENEXIST = 0,
		CREATENEW = 1,
		READWRITE = 2
	};

	class CPackageFile
	{
	private:
		char	m_szPath[MAX_PATH];
		char	m_szPath[MAX_PATH];
		bool	m_bCreateNew;
		bool	m_bReadOnly;

		FILE*	m_pFile1;
		FILE*	m_pFile2;

		__int64 m_size1;
		__int64 m_size2;

		__int64 m_filePos;

	public:
		CPackageFile();
		~CPackageFile();

		bool Open(const char* szFileName, bool bCreateNew, bool bReadOnly);

		bool Phase2Open(unsigned __int64 dwOffset);

		bool Phase2Create();

		bool Close();

		size_t read(void *buffer, size_t size, size_t count);
		size_t write(const void * buffer, size_t size, size_t count);
		void flush();
		void seek(__int64 offset, int origin);
		unsigned __int64 tell() const;

		inline unsigned __int64 GetPackageFileSize() const { return unsigned __int64(m_size1 + m_size2); }
		void SetPackageFileSize(unsigned __int64 dwFileSize);

		bool IsSizeOver() const;

		static unsigned __int64 MaximumFileSize();

		static void SetMaximumFileSize(unsigned __int64 size);

	private:
		unsigned __int64 MaximumSize1() const;
	};

	struct FILEENTRY_READ;

	enum
	{
		ENTRY_FILESTRLEN = 260
	};

#pragma pack(push, 1)
	struct FILEENTRY_22
	{
		char	szFileName[ENTRY_FILESTRLEN];
		DWORD	dwOffset;
		DWORD	dwLength;
		DWORD	dwCompressedLength;

		int		iAccessCnt;
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct FILEENTRY
	{
		char	szFileName[ENTRY_FILESTRLEN];
		unsigned __int64	dwOffset;
		DWORD	dwLength;
		DWORD	dwCompressedLength;

		int		iAccessCnt;

		void operator = (const FILEENTRY_READ& ent)
		{
			if (ent.szFileName)
				strcpy(szFileName, ent.szFileName);
			else
				szFileName[0] = 0;
			dwOffset = ent.dwOffset;
			dwLength = ent.dwLength;
			dwCompressedLength = ent.dwCompressedLength;
			iAccessCnt = ent.iAccessCnt;
		}
	};
#pragma pack(pop)

	struct FILEENTRYCACHE
	{
		DWORD	dwCompressedLength;
		BYTE*	pEntryCompressed;

		FILEENTRYCACHE() : dwCompressedLength(0), pEntryCompressed(0) {}
		bool ResizeBuffer(size_t new_size);
		void ClearBuffer();
	};

	struct FILEENTRY_READ
	{
		char*	szFileName;
		unsigned __int64 dwOffset;
		DWORD	dwLength;
		DWORD	dwCompressedLength;

		int		iAccessCnt;
		bool	bRemoved;

		void operator = (const FILEENTRY& entry)
		{
			szFileName = new char[strlen(entry.szFileName) + 1];
			strcpy(szFileName, entry.szFileName);
			dwOffset = entry.dwOffset;
			dwLength = entry.dwLength;
			dwCompressedLength = entry.dwCompressedLength;
			iAccessCnt = entry.iAccessCnt;
		}

		bool isValid() const
		{
			return !bRemoved;
		}

		FILEENTRY_READ() : szFileName(0), dwOffset(0), dwCompressedLength(0), iAccessCnt(0), bRemoved(false) {}
		~FILEENTRY_READ()
		{
			delete[] szFileName;
		}

	};

#pragma pack(push, 1)
	struct FILEHEADER_22
	{
		DWORD	guardByte0;
		DWORD	dwVersion;
		DWORD	dwEntryOffset;
		DWORD	dwFlags;
		char	szDescription[252];
		DWORD	guardByte1;
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct FILEHEADER
	{
		DWORD	guardByte0;
		unsigned __int64	dwEntryOffset;
		DWORD	dwFlags;
		char	szDescription[252];
		DWORD	guardByte1;
	};
#pragma pack(pop)

	struct SHAREDFILE
	{
		DWORD	dwFileID;
		bool	bCached;
		int		iRefCnt;
		BYTE*	pFileData;
		DWORD	dwFileLen;

		FILEENTRY_READ* pFileEntry;
	};

	struct CACHEFILENAME
	{
		std::string strFileName;
		DWORD		dwFileID;
	};

#pragma pack(push, 1)
	struct SAFEFILEHEADER_22
	{
		DWORD	tag1;
		DWORD	offset;
		DWORD	tag2;
	};

	struct SAFEFILEHEADER
	{
		DWORD	tag1;
		unsigned __int64 offset;
	};
#pragma pack(pop)

	typedef std::hash_map<SHAREDFILE*, int>		SharedTable;
	typedef std::hash_map<CACHEFILENAME, int>	CachedTable;

	friend class AFilePackMan;
	

private:

	bool		m_bHasChanged;
	bool		m_bReadOnly;
	bool		m_bUseShortName;

	FILEHEADER	m_header;
	OPENMODE	m_mode;

	std::vector<FILEENTRY_READ*>	m_aFileEntries;
	FILEENTRY_READ*					m_pFileEntriesBuf;
	std::vector<FILEENTRYCACHE>		m_aFileEntryCache;

	CachedTable						m_CachedFileTab;
	SharedTable						m_SharedFileTab;

	CPackageFile*					m_fpPackageFile;
	char							m_szPckFileName[MAX_PATH];
	char							m_szFolder[MAX_PATH];

	directory						m_directory;
	DWORD							m_dwCacheSize;
	DWORD							m_dwSharedSize;
	file*							m_pFileBuf;
	int								m_nFileBufIndex;

	SAFEFILEHEADER					m_safeHeader;

public:

	AFilePackage();
	~AFilePackage();

	bool Open(const char* szPckPath, OPENMODE mode, bool bEncrypt = false);
	bool Open(const char* szPckPath, const char* szFolder, OPENMODE mode, bool bEncrypt = false);
	bool Close();
	bool IsReadOnly() const { return m_bReadOnly; }
	static void PreReadFilePackageDir(const char* szDir);

	bool AppendFile(const char* szFileName, LPBYTE pFileBuffer, DWORD dwFileLength, bool bCompress);
	bool AppendFileCompressed(const char* szFileName, LPBYTE pCompressedBuffer, DWORD dwFileLength, DWORD dwCompressedLength);

	bool RemoveFile(const char* szFileName);

	bool MarkFileAsRemoved(const char* szFileName);

	void CommitRemovedFile();

	bool ReplaceFile(const char* szFileName, LPBYTE pFileBuffer, DWORD dwFileLength, bool bCompress);
	bool ReplaceFileCompressed(const char* szFileName, LPBYTE pCompressedBuffer, DOWRD dwFileLength, DWORD dwCompressedLength);

	bool ResortEntries();

	bool ReadFile(const char* szFileName, LPBYTE pFileBuffer, DWORD* pdwBufferLen);
	bool ReadFile(FILEENTRY& fileEntry, LPBYTE pFileBuffer, DWORD* pdwBufferLen);

	bool ReadCompressedFile(const char* szFileName, LPBYTE pCompressedBuffer, DWORD* pdwBufferLen);
	bool ReadCompressedFile(FILEENTRY& fileEntry, LPBYTE pCompressedBuffer, DWORD* pdwBufferLen);

	bool GetFileEntry(const char* szFileName, FILEENTRY* pFileEntry, int* pnIndex = NULL);

	int GetFileNumber() const { return (int)m_aFileEntries.size(); }

	const FILEENTRY_READ* GetFileENtryByIndex(int nIndex)const { return m_aFileEntries[nIndex]; }

	size_t GetValidFileNumber() const;

	directory* GetDirEntry(const char* szPath);

	void ClearFileCache();

	auptrint OpenShaderFile(const char* szFileName, BYTE** ppFileBuf, DWORD* pwFileLen);

	void CloseSharedFile(auptrint dwFileHandle);

	DWORD GetCachedFileSize() const { return m_dwCacheSize; }
	DWORD GetSharedFileSize() const { return m_dwSharedSize; }

	FILEHEADER GetFIleHeader() const { return m_header; }
	const char* GetFolder() { return m_szFolder; }
	const char* GetPckFileName() { return m_szPckFileName; }

	unsigned __int64 GetPackageFileSize() { return m_fpPackageFile->GetPackageFileSize(); }

	static unsigned __int64 GetMaximumPackageFileSize() { return CPackageFile::MaximumFileSize(); }

	static void SetMaximumPackageFileSize(unsigned __int64 size) { return CPackageFile::SetMaximumFileSize(size); }


	enum ENTRY_OP_TYPE
	{
		ENTRY_OP_ADD,
		ENTRY_OP_REPLACE,
		ENTRY_OP_DELETE,
	};

	struct Cached_Writed_Entry
	{
		Cached_Writed_Entry() 
			:pEntry(0),
			strFileName(""),
			eEntryOpType(-1)
		{}

		FILEENTRY_READ* pEntry;
		FILEENTRYCACHE EntryCache;
		std::string strFileName;

		int eEntryOpType;
	};

	typedef std::vector<Cached_Writed_Entry>			Cached_Writed_Entry_Array;
	typedef std::map<std::string, Cached_Writed_Entry>	Cached_Writed_Entry_Map;

	struct File_Hole
	{
		unsigned __int64 dwStart;
		DWORD dwLength;

		bool operator<(const File_Hole& fh)
		{
			return dwLength < fh.dwLength;
		}
	};
	//typedef std::vector<File_Hole>	File_Hole_Array;
	//File_Hole_Array m_aFileHoles;
	//bool BeginAppendFileToPck();
	//bool ApendFileToPck()


public:

	static int Uncompress(LPBYTE pCompressedBuffer, DWORD dwCompressedLength, LPBYTE pFileBuffer, DWORD * pdwFileLength);
	bool AddCacheFileNameList(const char* szDescFile);
	bool AddCacheFileName(const char* szFile);

protected:

	static bool NormalizeFileName(char * szFileName);
	bool NormalizeFileName(char * szFileName, bool bUseShortName);
	void GetRidOfFolder(const char* szInName, char * szOutName);

	bool InnerOpen(const char* szPckPath, const char* szFolder, OPENMODE mode, bool bEncrypt, bool bShortName);

	bool RemoveFileFromDir(const char* filename);
	bool InsertFileToDir(const char * filename, int index);

	CACHEFILENAME* SearchCacheFileName(const char* szFileName);
	CACHEFILENAME* SearchCacheFileName(DWORD dwFileID);

	void SaveEntries();
	void Encrypt(LPBYTE pBuffer, DWORD dwLength);
	void Decrypt(LPBYTE pBuffer, DWORD dwLength);

	bool LoadOldSafeHeader();
	bool LoadSafeHeader();
	bool SaveSafeHeader();
	void CreateSafeHeader();

	static SAFEFILEHEADER ConvertOldSafeHeader(SAFEFILEHEADER_22 const& safeHeader_22);

	bool LoadHeader_22(int version, FILEHEADER_22& fileHeader_22);
	static FILEHEADER ConvertFileHeader_22To23(FILEHEADER_22 const& fileHeader_22);
	bool LoadHeader(DWORD version);
	bool SaveHeader();
	void CreateHeader(bool bEncrypt);

	bool MakeEntry_22(DWORD version, BYTE* compressedData, DWORD compressedSize, FILEENTRY_22* pEntry);
	static void ConvertEntry_22To23(FILEENTRY_22 const& entry_22, FILEENTRY* pEntry);

	bool MakeEntry(DWORD version, BYTE* compressedData, DWORD compressedSize, FILEENTRY* pEntry, FILEENTRYCACHE* pEntryCache);
	void FillEntryCache(FILEENTRY const* pEntry, FILEENTRYCACHE* pEntryCache);
};


class AFilePackMan
{
private:
	std::vector<AFilePackage*> m_FilePcks;
	bool m_bReadOnly;
	bool m_bKeepFullPath;
	bool m_bInitCompleted;
	afilepack_mem_man m_MemMan;

	bool m_bReadWrite;

public:
	AFilePackMan();
	~AFilePackMan();

	bool SetAlgorithmID(int id);


	bool OpenFilePackage(const char* szPckFile, bool bCreateNew = false, bool bEncrypt = false);
	bool CreateFilePackage(const char* szPckFile, const char* szFolder, bool bEncrypt = false);
	bool OpenFilePackage(const char* szPckFile, const char* szFolder, bool bEncrypt = false);

	bool CloseFilePackage(AFilePackage* pFilePck);

	bool CloseAllPackages();

	int GetNumPackages();

	AFilePackage* GetFilePck(int index);

	AFilePackage* GetFilePck(const char* szPath);

	bool ReadFile(const char* szFileName, LPBYTE pFileBuffer, DWORD* pdwBufferLen);

	void SetReadOnly(bool b);
	bool IsReadOnly() const{ return m_bReadOnly; }
	void SetKeepFullPath(bool b) { m_bKeepFullPath = b; }
	bool IsKeepFullPath() const { return m_bKeepFullPath; }

	void SetReadWrite(bool b);
	bool IsReadWrite() const { return m_bReadWrite; }

	void SetInitCompleted() { m_bInitCompleted = true; }

	afilepack_mem_man& GetmemMan() { return m_MemMan; }
};

extern AFilePackMan g_AFilePackMan;