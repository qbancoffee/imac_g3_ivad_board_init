/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package imacg3dvdisplayproperties;

/**
 *
 * @author Rocky Hill
 */
import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;
import java.io.PrintStream;
import java.util.Calendar;
import java.util.Enumeration;

public class SerialTrigger implements Runnable {

    private boolean stopped = false;
    private SerialPort port = null;
    private CommPortIdentifier portId = null;
    private long currentTime;
    private long startTime;
    private long elapsedTime = 0;
    private boolean sent = false;
    private String portName="";

    private char characterToSend = '\0';

    @Override
    public void run() {

        currentTime = Calendar.getInstance().getTimeInMillis();
        startTime = Calendar.getInstance().getTimeInMillis();
        while (!stopped) {
            
            currentTime = Calendar.getInstance().getTimeInMillis();
            elapsedTime = currentTime - startTime;
 
            if (!sent || elapsedTime >= 250) {
                sent =true;
                try {

                    Thread.sleep(10L);
                    

                    if (port != null) {
                        System.out.println(characterToSend);

                        PrintStream os;

                        os = new PrintStream(port.getOutputStream());
                        os.print(characterToSend);

                        if (os != null) {
                            os.flush();
                            os.close();
                            os = null;
                        }

                    }//end if       

                } catch (Exception e) {
                    e.printStackTrace();
                }//end catch
            }//end if
            
           
        }//end while
    }

    public void setCharacter(char c) {
        characterToSend = c;
    }//end mehtod

    public void stopThread() {
        stopped=true;
//        try {
//            stopped = true;
//
//            if (port != null) {
//                port.close();
//                //Thread.sleep(25);
//                port = null;
//
//            }//end if        
//
//            if (portId != null) {
//                portId = null;
//
//            }//end if
//
//        }//end try
//        catch (Exception e) {
//            e.printStackTrace();
//        }//end catch
    }
public void setPort(SerialPort p){
port=p;
}//end method


}//end class
