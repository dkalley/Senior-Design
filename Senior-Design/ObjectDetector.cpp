#include "pch.h"
#include "ObjectDetector.h"
#include "MyTuioListener.h"

using namespace TUIO;

void temp()
{

}


// STILL NEED TO FIGURE OUT
ObjectDetector::ObjectDetector()
{
	MyTuioListener *mylistener;
	//receiver = new TcpReceiver(3333);
}
/*
void ObjectDetector::StartClient()
{
	try
	{
		// Create the StreamSocket and establish a connection to the echo server.
		//streamSocket = new Windows::Networking::Sockets::StreamSocket();
		
		// The server hostname that we will be establishing a connection to. In this example, the server and client are in the same process.
		//auto hostName = ref new Windows::Networking::HostName(L"localhost");
		
		HostName hostname{ L"localhost" };

		//this->clientListBox->Items->Append(L"client is trying to connect...");

		create_task(streamSocket.ConnectAsync(hostname, L"3333")).then(
			[=](Concurrency::task< void >)
			{
				//this->clientListBox->Items->Append(L"client connected");

				// Send a request to the echo server.
				DataWriter dataWriter(streamSocket.OutputStream());
				auto request = new String(L"Hello, World!");
				dataWriter.WriteUInt32(request->Length());
				dataWriter.WriteString(request);

				Concurrency::create_task(dataWriter.StoreAsync()).then(
					[=](Concurrency::task< unsigned int >)
					{
						std::wstringstream wstringstream;
						wstringstream << L"client sent the request: \"" << request->Data() << L"\"";
						//this->clientListBox->Items->Append(ref new Platform::String(wstringstream.str().c_str()));

						Concurrency::create_task(dataWriter.FlushAsync()).then(
							[=](Concurrency::task< bool >)
							{
								dataWriter.DetachStream();

								// Read data from the echo server.
								DataReader dataReader(streamSocket.InputStream());
								Concurrency::create_task(dataReader.LoadAsync(sizeof(unsigned int))).then(
									[=](unsigned int bytesLoaded)
									{
										unsigned int stringLength = dataReader.ReadUInt32();
										Concurrency::create_task(dataReader.LoadAsync(stringLength)).then(
											[=](unsigned int bytesLoaded)
											{
												Platform::String^ response = dataReader.ReadString(bytesLoaded);
												this->Dispatcher->RunAsync(CoreDispatcherPriority::Normal, ref new DispatchedHandler(
													[=]
													{
														std::wstringstream wstringstream;
														wstringstream << L"client received the response: \"" << response->Data() << L"\"";
														//this->clientListBox->Items->Append(ref new Platform::String(wstringstream.str().c_str()));

														streamSocket = {nullptr};
														this->streamSocket = nullptr;

														//this->clientListBox->Items->Append(L"client closed its socket");
													}));
											});
									});
							});
					});
			});
	}
	catch (Platform::Exception^ ex)
	{
		Windows::Networking::Sockets::SocketErrorStatus webErrorStatus = Windows::Networking::Sockets::SocketError::GetStatus(ex->HResult);
		this->serverListBox->Items->Append(webErrorStatus.ToString() != L"Unknown" ? webErrorStatus.ToString() : ex->Message);
	}
}

*/

