<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<meta http-equiv="X-UA-Compatible" content="IE=edge">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<title>HCIN720 Group Project</title>
</head>
<body>

<h1>Car Simulator</h1>

<h2> Project Description </h2>
Our team embarked on a fascinating project to create a car simulator that goes beyond coding by integrating real-world sensor functionalities into a small 3D-printed truck model. The simulator monitors crucial aspects of a vehicle, including temperature, ultrasonic range, and light conditions. Using a 3D printer, we meticulously crafted a detailed truck model, equipped it with an array of sensors mirroring those found in actual cars, and proceeded to manufacture this miniature marvel.
	
<h2>Construction Video</h2>
<video src="https://user-images.githubusercontent.com/169707/.mp4" controls="controls" style="max-width: 730px;">
</video>
	
<h2>Parts List</h2>
<p><ul>
  <li><strong>MOTION_SENSOR:</strong> Pin for the motion sensor.</li>
  <li><strong><a href ="https://wiki.seeedstudio.com/Grove-Circular_LED/">
	  Circular LED  </a></strong> For Low beam and High beam to simulate passing</li>
  <li><strong><a href = "https://wiki.seeedstudio.com/Grove-Ultrasonic_Ranger/">
	  Ultrasound Ranger </a></strong> For measuring the distance between your car and behind, alert if it is too close.</li>
  <li><strong><a href = "https://wiki.seeedstudio.com/Grove-TemperatureAndHumidity_Sensor/">
	  Temperature and Humidity Sensor </a></strong> Check the temperature rather it is good or bad for driving. </li>
  <li><strong><a href = "https://wiki.seeedstudio.com/Grove-Digital_Light_Sensor/">
	  Digital Light Sensor </a></strong>  For Low beam and High beam to simulate passing</li>
</ul></p>
	
<h2>Step1: Creating a Truck by using the 3D Printer </h2>
	
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

</body>
</html>
