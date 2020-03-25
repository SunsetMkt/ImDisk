///
/// Some additional native user-mode API functions we use
///

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _UNICODE_STRING {
    USHORT Length;
    USHORT MaximumLength;
    PWSTR  Buffer;
} UNICODE_STRING;
typedef UNICODE_STRING *PUNICODE_STRING;
typedef const UNICODE_STRING *PCUNICODE_STRING;
#define UNICODE_NULL ((WCHAR)0)

typedef LONG NTSTATUS;
typedef NTSTATUS *PNTSTATUS;

typedef struct _OBJECT_ATTRIBUTES {
    ULONG Length;
    HANDLE RootDirectory;
    PUNICODE_STRING ObjectName;
    ULONG Attributes;
    PVOID SecurityDescriptor;
    PVOID SecurityQualityOfService;
} OBJECT_ATTRIBUTES;
typedef OBJECT_ATTRIBUTES *POBJECT_ATTRIBUTES;

typedef struct _IO_STATUS_BLOCK {
    union {
        NTSTATUS Status;
        PVOID Pointer;
    };

    ULONG_PTR Information;
} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;

#define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)

#define OBJ_CASE_INSENSITIVE    0x00000040L

#define InitializeObjectAttributes( p, n, a, r, s ) { \
    (p)->Length = sizeof(OBJECT_ATTRIBUTES);	      \
    (p)->RootDirectory = r;			      \
    (p)->Attributes = a;			      \
    (p)->ObjectName = n;			      \
    (p)->SecurityDescriptor = s;		      \
    (p)->SecurityQualityOfService = NULL;	      \
} 

#define FILE_SYNCHRONOUS_IO_NONALERT            0x00000020
#define FILE_NON_DIRECTORY_FILE                 0x00000040

typedef struct _REPARSE_DATA_JUNCTION
{
  DWORD ReparseTag;
  WORD ReparseDataLength;
  WORD Reserved;
  WORD NameOffset;
  WORD NameLength;
  WORD DisplayNameOffset;
  WORD DisplayNameLength;
  BYTE Data[65536];
} REPARSE_DATA_JUNCTION, *PREPARSE_DATA_JUNCTION;

NTSYSAPI 
BOOLEAN 
NTAPI 
RtlDosPathNameToNtPathName_U(IN PCWSTR DosName,
			     OUT PUNICODE_STRING NtName,
			     OUT PCWSTR *DosFilePath OPTIONAL,
			     OUT PUNICODE_STRING NtFilePath OPTIONAL);

NTSYSAPI 
BOOLEAN 
NTAPI 
RtlCreateUnicodeString(OUT PUNICODE_STRING DestinationString,
		       IN PCWSTR SourceString);

NTSYSAPI 
VOID
NTAPI
RtlFreeUnicodeString(IN PUNICODE_STRING UnicodeString);

NTSYSAPI 
VOID
NTAPI
RtlInitUnicodeString(IN OUT PUNICODE_STRING DestinationString,
		     IN PCWSTR SourceString);

NTSYSAPI 
NTSTATUS
NTAPI
NtOpenFile(OUT PHANDLE  FileHandle,
	   IN ACCESS_MASK  DesiredAccess,
	   IN POBJECT_ATTRIBUTES  ObjectAttributes,
	   OUT PIO_STATUS_BLOCK  IoStatusBlock,
	   IN ULONG  ShareAccess,
	   IN ULONG  OpenOptions);

NTSYSAPI 
BOOLEAN 
NTAPI 
NtClose(IN HANDLE hObject);

NTSYSAPI 
ULONG
NTAPI 
RtlNtStatusToDosError(NTSTATUS Status);

NTSYSAPI
NTSTATUS
WINAPI
RtlGetVersion(
__inout __deref
POSVERSIONINFOW lpVersionInformation);

#ifdef __cplusplus
}
#endif
