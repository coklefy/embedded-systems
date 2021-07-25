package view;

import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;

import communication.Controller;
import java.awt.FlowLayout;
import javax.swing.SwingConstants;

public class SmartCoffeeMachineView extends JFrame  {


	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private JTextField jCoffeeQ;
	private JButton bCoffeeQ, refillCoffee;

	private JTextField jZuccheroQ;
	private JButton bZuccheroQ;
        private JTextField messages;


        public SmartCoffeeMachineView(){
	    super("Smart Coffee Machine View");
	    setSize(762,134);
	    
	    JPanel mainPanel = new JPanel();
	    mainPanel.setLayout(new FlowLayout(FlowLayout.CENTER, 5, 5));

            JPanel reqMsgPanel = new JPanel();
            reqMsgPanel.setLayout(new BoxLayout(reqMsgPanel, BoxLayout.LINE_AXIS));
            reqMsgPanel.add(new JLabel("Messages: "));
            messages = new JTextField(60);
            reqMsgPanel.add(messages);
            mainPanel.add(reqMsgPanel);	    
	    bCoffeeQ = new JButton("Get coffee quantity");
	    mainPanel.add(bCoffeeQ);
	    
	    JPanel reqCoffeeQ = new JPanel();
	    reqCoffeeQ.setLayout(new BoxLayout(reqCoffeeQ, BoxLayout.LINE_AXIS));
	    jCoffeeQ = new JTextField(40);
	    jCoffeeQ.setEditable(false);
	    reqCoffeeQ.add(jCoffeeQ);
	    refillCoffee = new JButton("Refill coffee");
	    reqCoffeeQ.add(refillCoffee);
	    mainPanel.add(reqCoffeeQ);
	    bZuccheroQ = new JButton("Zucchero quantity");
	    mainPanel.add(bZuccheroQ);
	    bZuccheroQ.setVerticalAlignment(SwingConstants.TOP);
	    
	    JPanel reqZuccheroQ = new JPanel();
	    reqZuccheroQ.setLayout(new BoxLayout(reqZuccheroQ, BoxLayout.LINE_AXIS));
	    jZuccheroQ = new JTextField(40);
	    reqZuccheroQ.add(jZuccheroQ);
	    mainPanel.add(reqZuccheroQ);

	    this.getContentPane().add(mainPanel);
	    
	    addWindowListener(new WindowAdapter(){
	      public void windowClosing(WindowEvent ev){
	        System.exit(-1);
	      }
	    });
	  }

	  public void registerController(Controller contr){
		  bCoffeeQ.addActionListener(contr);
		  bZuccheroQ.addActionListener(contr);
		  refillCoffee.addActionListener(contr);		  
	  }
	  


	  public void setJcoffeeQ(String msg){
		  SwingUtilities.invokeLater(() -> {
			 jCoffeeQ.setText(msg);
		  });
	  }

	  public void setJzuccheroQ(String msg){
		  SwingUtilities.invokeLater(() -> {
			 jZuccheroQ.setText(msg);
		  });
	  }
	  
	  
	public void noCoffee() {
		
		String message = "NO MORE COFFEE. Refill coffee to FULL!!!";
		    JOptionPane.showMessageDialog(new JFrame(), message, "Dialog",
		        JOptionPane.ERROR_MESSAGE);
		
	}
	
        public void displayMsg(String msg){
            SwingUtilities.invokeLater(() -> {
                   messages.setText(msg);
            });
    }

	
	}
