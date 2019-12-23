package ftpClient;

import java.io.IOException;

public class FTPClient {

	public static void main(String[] args) {
	
		int port = 2020;
		FTPOioClient server = new FTPOioClient();
		String ServerAddr = "127.0.0.1";
		
		if(args.length > 0) {
			port = Integer.parseInt(args[0]);
		}
		
		try {
			server.request(ServerAddr, port);
		} catch (IOException e) {
			e.printStackTrace();
			System.out.println("ERROR: Failed to create the Client Socket.");
		}
		
	}

}
