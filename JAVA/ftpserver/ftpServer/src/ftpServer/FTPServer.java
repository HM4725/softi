package ftpServer;

import java.io.IOException;

public class FTPServer {

	public static void main(String[] args) {

		int port = 2020;
		FTPOioServer server = new FTPOioServer();

		if(args.length > 0) {
			port = Integer.parseInt(args[0]);
		}
		
		try {
			server.serve(port);
		} catch (IOException e) {
			e.printStackTrace();
			System.out.println("ERROR: Failed to create the Server Socket.");
		}
		
	}

}
