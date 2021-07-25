package monitor;

import view.*;
import communication.*;


public class MonitoringAgent extends Thread {

	SerialCommChannel channel;
	SmartCoffeeMachineView view;
	
	public MonitoringAgent(SerialCommChannel channel, SmartCoffeeMachineView view) throws Exception {
		this.view = view;
		this.channel = channel;
	}
	
	public void run(){
		while (true){
			try {
				String msg = channel.receiveMsg();
				
				if (msg.startsWith("display:")){
                                    view.displayMsg(msg.substring(8));
				} else if (msg.startsWith("req_coffeeQ:")) {
					view.setJcoffeeQ(msg.substring(12));
				} else if (msg.startsWith("req_zucchero:")) {
					view.setJzuccheroQ(msg.substring(13));
				} else if(msg.startsWith("no_coffee")) {
					view.noCoffee();
				}
			} catch (Exception ex){
				ex.printStackTrace();
			}
		}
	}

}
