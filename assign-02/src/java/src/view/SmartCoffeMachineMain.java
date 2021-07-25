package view;

import communication.Controller;

class SmartCoffeMachineMain   {

	public static void main(String[] args) throws Exception {
		SmartCoffeeMachineView view = new SmartCoffeeMachineView();
		Controller contr = new Controller("COM7",view);
		view.registerController(contr);
		view.setVisible(true);

	}
}