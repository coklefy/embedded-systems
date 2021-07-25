package communication;

import java.util.Enumeration;

import gnu.io.CommPortIdentifier;

/**
 * Show the serial ports available on the PC
 *
 * @author aricci
 *
 */
public class ShowSerialPorts {

	public static void main(String[] args) throws Exception {

		Enumeration portEnum = CommPortIdentifier.getPortIdentifiers();
		while (portEnum.hasMoreElements()) {
			CommPortIdentifier currPortId = (CommPortIdentifier) portEnum
					.nextElement();
			System.out.println(currPortId.getName());
		}

	}
}
