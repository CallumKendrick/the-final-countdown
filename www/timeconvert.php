<?php


	
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

		
		return $timeArray;

	}
	
?>