

<h1>Car Simulator</h1>

<h2> Project Description </h2>
Our team embarked on a fascinating project to create a car simulator that goes beyond coding by integrating real-world sensor functionalities into a small 3D-printed truck model. The simulator monitors crucial aspects of a vehicle, including temperature, ultrasonic range, and light conditions. Using a 3D printer, we meticulously crafted a detailed truck model, equipped it with an array of sensors mirroring those found in actual cars, and proceeded to manufacture this miniature marvel.
	
<h2>Construction Video</h2>
<video src="https://github.com/gautham-2803/Arduino/assets/57102558/046af277-7ecd-4458-945f-b1d749e6d3d6" >
</video>




	
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
</ul></p>
	
<h2>Step1: Connect the Circular LED to D2 </h2>
	
<h2>Step2: Flashing the light</h2>
	<h3> This function is used to check the presence of an object to the right. It is useful while passing lanes.</h3>
	
	<h2>GetReadyMessage</h2>
	This function is initially executed when there is a remote start command from the user. This simulates systems check and welcome address.
	
	<h2>StartEngine</h2>	
	This function is executed second. This simulates engine start and checks the weather to give notification on it. 
	
	<h2>ReadAndLightFront</h2>	
	This functions turns on light sensor automatically based on the light value. On pressing WIO_5S_PRESS down, the light switches to low beam and high beam, to simulate passing. 
	
	<h2>getTemperature</h2>	
	//this function is used to monitor engine temperature. This gets activated when you press WIO_KEY_B

	<h2>ReadUltrasonic</h2>	
	//This is used to measure the distance between your car and the car behind. An alert will be issued on the LCD if its too close
 <h2>Remote Start</h2>
 
	 
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
<hr>

