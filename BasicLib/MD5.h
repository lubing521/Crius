#pragma once
class CMD5 {
public:
	CMD5();
	CMD5(const VOID *input, size_t length);
	VOID Update(const VOID *input, size_t length);
	
	const LPBYTE Digest();
	std::string ToString();
	VOID Reset();

private:
	VOID Update(const LPBYTE input, size_t length);
	VOID Final();
	VOID Transform(const BYTE block[64]);
	VOID Encode(const PUINT input, LPBYTE output, size_t length);
	VOID Decode(const LPBYTE input, PUINT output, size_t length);
	std::string BytesToHexString(const BYTE *input, size_t length);
	CMD5(const CMD5&);
	CMD5& operator=(const CMD5&);

private:
	UINT mState[4];
	UINT mCount[2];	
	BYTE mBuffer[64];	
	BYTE mDigest[16];	
	BOOL Finished;		
	static const BYTE PADDING[64];	
	static const CHAR HEX[16];
	enum { BUFFER_SIZE = 1024 };
};

