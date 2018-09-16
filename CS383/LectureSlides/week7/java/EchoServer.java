import java.net.*;
import java.io.*;

public class EchoServer {

    public static void main(String[] args) {

      try{
        
          ServerSocket server = new ServerSocket(5555); //listen to port 8080


        System.out.println("Waiting Incoming Connection...");
        Socket sock = server.accept();

        BufferedReader instream = new BufferedReader (new InputStreamReader (sock.getInputStream()));
        BufferedWriter outstream = new BufferedWriter(new OutputStreamWriter(sock.getOutputStream()));

        String strin = instream.readLine();
        boolean echo = false;

        if (strin.equals("Hello")){ //following the protocol
                outstream.write("Welcome"+"\n");
                outstream.flush();
                echo = true;
         }
        else {  //not following the protocol
            	//write your code
            if (!echo){
                outstream.write("Not Welcome"+"\n");
                outstream.flush();
            }
            if (echo) {
                if (strin.equals("bye")) {
                    outstream.write("bye"+"\n");
                    outstream.flush();
                    echo = false;
                }
                else{
                    outstream.write(strin);
                    outstream.flush();
                }
            }
        }
        instream.close();
        outstream.close();
        sock.close();
        System.out.println("Connection Closing...");

        }
      catch (Exception ex){
            System.out.println("Error during I/O");
            ex.getMessage();
            ex.printStackTrace();
        }    
    } 
}
