package communication;

import view.*;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import monitor.MonitoringAgent;

public class Controller implements ActionListener {

	SerialCommChannel channel;
	SmartCoffeeMachineView view;
	
	public Controller(String port, SmartCoffeeMachineView view) throws Exception {
		this.view = view;
		channel = new SerialCommChannel(port,9600);		
		new MonitoringAgent(channel,view).start();
			
		/* attesa necessaria per fare in modo che Arduino completi il reboot */
		System.out.println("Waiting Arduino for rebooting...");		
		Thread.sleep(4000);
		System.out.println("Ready.");		
	
	}
	
	public void actionPerformed(ActionEvent ev){
		  try {
			  if (ev.getActionCommand().equals("Get coffee quantity")){
					channel.sendMsg("req_coffeeQ");
			  } else if (ev.getActionCommand().equals("Refill coffee")) {
				  	channel.sendMsg("refill_coffee");
			  }
		  } catch (Exception ex){
			  ex.printStackTrace();
		  }
	  }

}
