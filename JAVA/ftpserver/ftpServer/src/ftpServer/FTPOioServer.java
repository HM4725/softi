package ftpServer;

import java.io.*;
import java.net.*;

public class FTPOioServer {

public void serve(int port) throws IOException {
		
		final ServerSocket socket = new ServerSocket(port);
		
		try {
			while(true) {
				final Socket clientSocket = socket.accept();
				System.out.println("Accepted connection from " + clientSocket);

				new Thread(new Runnable() {
					public void run() {
						try {
							FTPServerProcess process = new FTPServerProcess(clientSocket);
							process.run();
							clientSocket.close();
						} catch (IOException e) {
							e.printStackTrace();
							try { clientSocket.close(); } catch (IOException ex) { }
						}
					}
				}).start();
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
