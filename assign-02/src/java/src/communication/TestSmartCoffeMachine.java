package communication;

/**
 * Testing simple message passing.
 * 
 * To be used with an Arduino connected via Serial Port
 * running modulo-2.3/pingpong.ino
 * 
 * @author aricci
 *
 */
public class TestSmartCoffeMachine {

	public static void main(String[] args) throws Exception {
		SerialCommChannel channel = new SerialCommChannel("COM7",9600);		
		/* attesa necessaria per fare in modo che Arduino completi il reboot */
		System.out.println("Waiting Arduino for rebooting...");		
		Thread.sleep(4000);
		System.out.println("Ready.");		

		
		while (true){
			Thread.sleep(2000);
			System.out.println("Req state");
			channel.sendMsg("req_state");
			String msg = channel.receiveMsg();
			System.out.println("Received: "+msg);		
			Thread.sleep(500);
			channel.sendMsg("req_nusers");
			msg = channel.receiveMsg();
			System.out.println("Received: "+msg);		
			Thread.sleep(500);
			channel.sendMsg("req_nusages");
			msg = channel.receiveMsg();
			System.out.println("Received: "+msg);		
		}
	}

}
