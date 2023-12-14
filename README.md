

<h1>Car Simulator</h1>

<h2> Project Description </h2>
Our team embarked on a fascinating project to create a car simulator that goes beyond coding by integrating real-world sensor functionalities into a small 3D-printed truck model. The simulator monitors crucial aspects of a vehicle, including temperature, ultrasonic range, and light conditions. Using a 3D printer, we meticulously crafted a detailed truck model, equipped it with an array of sensors mirroring those found in actual cars, and proceeded to manufacture this miniature marvel.

<h2>Parts List</h2>
<p><ul>
  <li><strong><a href ="https://wiki.seeedstudio.com/Grove-PIR_Motion_Sensor/"> MOTION_SENSOR </a></strong> To detect the presence of an object while passing left.</li>
  <li><strong><a href ="https://wiki.seeedstudio.com/Grove-Circular_LED/">
	  Circular LED  </a></strong> To simulate front headlights.</li>
  <li><strong><a href = "https://wiki.seeedstudio.com/Grove-Ultrasonic_Ranger/">
	  Ultrasound Ranger </a></strong> To measure the distance between your car and behind.</li>
  <li><strong><a href = "https://wiki.seeedstudio.com/Grove-TemperatureAndHumidity_Sensor/">
	  Temperature and Humidity Sensor </a></strong> To simulate and measure the ambient and engine temperature.</li>
  <li><strong><a href = "https://wiki.seeedstudio.com/Grove-Digital_Light_Sensor/">
	  Digital Light Sensor </a></strong> To determine the outdoor light conditions.</li>
</ul>
</p>

<h2>Features</h2>
The project was developed with the following features:
<ul>
	<li>Simulate the start of the vehicle remotely.</li>
	<li>Turn on the light automatically by reading the light sensor value.</li>
	<li>Use the LED to simulate front headlights.</li>
	<li>Simulate High Beam and Low Beam.</li>
	<li>Provide an alert to the user if the Engine Temperature is high.</li>
	<li>Provide a proximity alert based on the car behind.</li>
	<li>Provide a blind spot audio alert while passing left.</li>
</ul>
<hr>

<h2>Setup Instructions</h2>
<ul>
<li>Step1: Connect the Circular LED to D2 </li>
<li>Step2: Connect the Ultrasonic Ranger to D4 </li>
<li>Step3: Connect the Digital Light Sensor to the I2C port on the Wio Terminal </li>
<li>Step4: Connect the Temperature and Humidity Sensor to D6 </li>
<li>Step5: Connect the PIR Motion Sensor to D0 </li>
<li>Step6: Attach the Wio to the 3D Printed Truck </li>

 </ul>
<br/>
<br/>
The below portrays the image representation for step-by-step connections:

<br/>
<br/>
<img src="https://github.com/gautham-2803/Arduino/assets/57102558/620f837c-0a32-4d4a-9d79-e465877c3bf7" width="100%">

	
<h2>Construction Video</h2>
<video src="https://github.com/gautham-2803/Arduino/assets/57102558/046af277-7ecd-4458-945f-b1d749e6d3d6" >
</video>


 <h2>Working Principle</h2>
 <h3>Remote Start</h3>
	 
 </ul>
 <li><a href="https://www.pushsafer.com/">Pushsafer</a> was used to send a command through Python to an iOS device that posed the question "Want to start your car?". </li>
 <li>If the user responded yes, a command was then sent to Wio which would simulate the start of a car engine. </li>
 <li>If no, the loop in Python would repeat after a set period that will ask the question again</li>
 </ul>
 <br/>
 The following images represent the screen from PushSafer. 
<br/>
<br>

<p float="left">
  <img src="https://github.com/gautham-2803/Arduino/assets/57102558/174b7cd9-fdd5-4bb1-8e21-d5edf834b60a"  width="33%"/> <img src="https://github.com/gautham-2803/Arduino/assets/57102558/16f4448e-2ca6-418e-b696-f2128ed980c7" width="33%"/> <img src="https://github.com/gautham-2803/Arduino/assets/57102558/dc590d71-de45-4814-8f07-d2bd0a239f87" width="33%">
</p>
<br/>
<h3>Passing on the left</h3>
<ul>
	<li>When WIO_KEY_C is pressed, the motion sensor is enabled to check for blind spot objects. </li>
	<li>This is done to simulate the indicator camera in cars.</li>
	<li>If an object is identified, the WIO_BUZZER is set to provide audio feedback in addition to the alert that appears on the terminal </li>
</ul>
<hr>

<h3>Rear end proximity detection</h3>
<ul>
	<li>The Ultrasonic Ranger is used to simulate rear end proximity detector.</li>
	<li>The ranger is set to run continuously and provides visual alerts on the terminal if the vehicle behind is close.</li>
	<li>If the vehicle behind is between 15 to 30m, the alert is issued as "CAR BEHIND", and when the vehicle is closer than that, the alert is issued as "ALERT!".</li>
</ul>

<h2>Working Video</h2>
<video src="https://github.com/gautham-2803/Arduino/assets/57102558/046af277-7ecd-4458-945f-b1d749e6d3d6" >
</video>

