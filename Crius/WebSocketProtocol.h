#pragma once
class CWebSocketProtocol
{
public:
	typedef CConnectionHandle<CWebSocketProtocol, const char *> Handler;
	CWebSocketProtocol();
	~CWebSocketProtocol();
public:
	BOOL Begin();
	BOOL End();
	VOID Translate(CConnectionSession<CWebSocketProtocol> &pConn, BYTE *data, DWORD dataLength);
	BOOL Write(CConnectionSession<CWebSocketProtocol> &, BYTE*, DWORD);
private:
	BOOL GetPacket76(CConnectionSession<CWebSocketProtocol> &pConn, DWORD64 &packetLength);
	BOOL GetPacket75(CConnectionSession<CWebSocketProtocol> &pConn, DWORD64 &packetLength);
	BOOL WritePacket76(CConnectionSession<CWebSocketProtocol> &pConn, BYTE *data, DWORD dataLength);
	BOOL WritePacket75(CConnectionSession<CWebSocketProtocol> &pConn, BYTE *data, DWORD dataLength);
	BOOL (CWebSocketProtocol::*GetPacket)(CConnectionSession<CWebSocketProtocol> &, DWORD64 &);
	BOOL (CWebSocketProtocol::*WritePacket)(CConnectionSession<CWebSocketProtocol> &, BYTE*, DWORD);
	BOOL HandShake(HttpRequestHeader &header, CConnectionSession<CWebSocketProtocol> &pConn);
private:
	DWORD mRemainLength;
	BYTE *mDataBuffer;
	BYTE *mPacketBuffer;
	BOOL mIshandShaked;	
	DWORD mWebsocketVersion;
};

