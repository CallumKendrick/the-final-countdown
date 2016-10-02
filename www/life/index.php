<?php

$request = $_GET["name"];

if ($request != NULL)
{
	request($request);
}

function request($request)
{
	$times = fopen("data.csv", "r");
	$timeLeft;
	while (($time = fgetcsv($times)) !== FALSE) {

		 $timeLeft = $time[1];
			
	}
	echo $timeLeft;
	return $timeLeft;
}

// echo strtotime("2015/10/01");
$death = 0;
$modifier = 0;

function lifeLeft($name, $sex, $birth, $cigarettes, $cocaine, $alcoholism, $alcohols)
{
	$birth = strtotime($birth);

	if($sex=="male")
	{
		$lifespan = 2240614861; //71 years
	}
	else
	{
		$lifespan = 2524611661; //80 years
	}
	
	
	//calculate modifier 
	$modifier = ($cigarettes * 828 + $alcohols * 23760 + $alcoholism * 82800 + $cocaine * 122400);
	$death = ($birth + $lifespan) - $modifier;
	
	$death = $death - time();
	// echo("Time left: " . $death . " seconds <br/>");
	
	file_put_contents("data.csv", $name . "," . ($death + time()) . "\n", FILE_APPEND);
	
	return $death;
}

function detailedTime($secs){

		$seconds = $secs;
		$minutes = 0;
		$hours = 0;
		$days = 0;
		$years = 0;

		while($seconds > 365 * 24 * 60 * 60){

			$seconds -= 365 * 24 * 60 * 60;
			$years += 1;

		}
		while ($seconds > 24 * 60 * 60) {
			
			$seconds -=  24 * 60 * 60;
			$days += 1;
		}
		while ($seconds > 60 * 60){

			$seconds -= 60 * 60;
			$hours += 1;

		}
		while ($seconds > 60) {
			
			$seconds -= 60;
			$minutes += 1;
		}

		$timeArray = [];
		$timeArray["seconds"] = $seconds;
		$timeArray["minutes"] =	$minutes;
		$timeArray["hours"] = $hours;
		$timeArray["days"] = $days;
		$timeArray["years"] = $years;
		
		$return = ($years . ":" . $days . ":" . $hours . ":" . $minutes . ":" . $seconds);
		return $return;

	}

// $secondsLeft = lifeLeft("George RR. Martin", "male", "1948/07/02", 0, 0, 0, 0);
// echo(detailedTime($secondsLeft));


?>