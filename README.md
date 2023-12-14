<h1> Team Green </h1>
<ul>
	<li> Anila Durbha </li>
	<li> Gautham Krishna </li>
	<li> Marie Lee </li>
</ul>

<h1>Car Simulator</h1>

<h2> Project Description </h2>
This project was inspired by <a href="https://www.tesla.com/">TESLA</a>. Given the alarming price of TESLA cars, we aimed to design a low-budget prototype that could potentially be a competitor to Chevy or Ford. 
We designed a semi-truck-based car that could mimic the features of a modern-day car such as automatic lights, proximity alerts, blind spot detection, and temperature insights. This was designed using a Wio terminal, 5 external sensors, and 3 buttons. 
A detailed part list and working principle are listed in the upcoming sections. 


<h2>Parts List</h2>
<p><ul>
  <li><strong><a href ="https://wiki.seeedstudio.com/Grove-PIR_Motion_Sensor/"> Motion Sensor</a></strong> To detect the presence of an object while passing left.</li>
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
<video controls="" width="800" height="500" muted="" loop="" autoplay="" src="https://github.com/gautham-2803/Arduino/assets/57102558/046af277-7ecd-4458-945f-b1d749e6d3d6" type="video/mp4">

</video>


 <h2>Working Principle</h2>
 <h3>Remote Start</h3>
	 
 <ul>
 <li><a href="https://www.pushsafer.com/">Pushsafer</a> was used to send a command through Python to an iOS device that posed the question "Want to start your car?". </li>
 <li>If the user responded yes, a command was then sent to Wio which would simulate the start of a car engine. </li>
 <li>If no, the loop in Python would repeat after a set period that will ask the question again</li>
 </ul>
 <br/>
 The following images represent the screen from PushSafer. 
<br/>
<br>

<p float="left">
  <img src="https://github.com/gautham-2803/Arduino/assets/57102558/174b7cd9-fdd5-4bb1-8e21-d5edf834b60a"  width="30%"/> <img src="https://github.com/gautham-2803/Arduino/assets/57102558/16f4448e-2ca6-418e-b696-f2128ed980c7" width="30%"/> <img src="https://github.com/gautham-2803/Arduino/assets/57102558/dc590d71-de45-4814-8f07-d2bd0a239f87" width="30%">
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
<hr>
<h3>Automatic Lights</h3>
<ul>
	<li>This was designed based on the automatic headlights in cars. </li>
	<li>Based on the light value from the digital light sensor, the LED lights up.</li>
	<li>This is particularly true when it comes to low light values.</li>
 	<li> On pressing down WIO_5S_PRESS button, the LED also simulates High and Low Beam.</li>
	
</ul>
<hr>
<h3>Temperature</h3>
<ul>
	<li> The Temperature and Humidity Sensor serves two purposes.</li>
	<li> During the initial startup, it is used to measure "ambient temperature" and issues visual feedback.</li>
	<li> The feedback will include either "Beautiful Weather" or "Bad Weather, Drive Safe!" based on the temperature. </li>
	<li>While the vehicle is running, and when WIO_KEY_B is pressed, the same sensor is used to measure "engine temperature".</li>
	<li>Visual feedback is provided based on the temperature and the variation is also depicted through changes in colors - Blue for normal and Red for high temperatures. </li>
</ul>
<hr>

<h2>Fitting with 3D printed Case</h2>
The below image shows various angles for the final fitted vehicle. 

<br>
<br>
<img src="https://github.com/gautham-2803/Arduino/assets/57102558/6e61344f-4bcf-43bd-a8e7-8debaeb51752" width="100%">
<hr>



<h2>Working Video</h2>
The final prototype is as below:
<br>
<video controls="" width="800" height="500" muted="" loop="" autoplay="" src="https://github.com/gautham-2803/Arduino/assets/57102558/6817db2a-09ae-4dd6-8046-f63643e04d88" type="video/mp4">
</video>




