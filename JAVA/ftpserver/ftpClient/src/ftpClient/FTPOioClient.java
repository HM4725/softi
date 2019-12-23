package ftpClient;

import java.io.IOException;
import java.net.Socket;

public class FTPOioClient {

	public void request(String Addr, int port) throws IOException {
		
		Socket connectionSocket = new Socket(Addr, port);
		
		try {
			FTPClientProcess process = new FTPClientProcess(connectionSocket);
			process.run();
			connectionSocket.close();

		} catch (IOException e) {
			e.printStackTrace();
			connectionSocket.close();
		}
	}
}
