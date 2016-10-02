<!DOCTYPE html>
<html>
<head>
	<title>Delay The Inevitable</title>

	<style type="text/css">
		#data{
			font-size: 20px;
			margin: 0 auto;
			width: 1000px;
		}
		.tablepad{
			padding-right: 10px;
		}

		body{
			background: black;
		}

		.main{
			color: white;
			font-family: "Helvetica Neue", Helvetica, Arial, sans-serif;
		}
		h1{
			font-size: 80px;
		}

		h1, h2{
			text-align: center;
		}


		.line{
			stroke: white;
			stroke-width: 3px;
		}

		#ecg{
			margin-left: 40%;
		}

	</style>
</head>
<body class="main">
	
	<script src="jquery-3.1.1.min.js"></script>
	<script src="d3.min.js"></script>
	<script type="text/javascript">
		
		function detailedTime(seconds){

			var dt = {

				"seconds" 	: seconds,
				"minutes" 	: 0,
				"hours"		: 0,
				"days"		: 0,
				"years"		: 0,
				"dead"		: false

			};
			while(dt.seconds > 365 * 24 * 60 * 60){

			dt.seconds -= 365 * 24 * 60 * 60;
			dt.years += 1;

			}
			while (dt.seconds > 24 * 60 * 60) {
				
				dt.seconds -=  24 * 60 * 60;
				dt.days += 1;
			}
			while (dt.seconds > 60 * 60){

				dt.seconds -= 60 * 60;
				dt.hours += 1;

			}
			while (dt.seconds > 60) {
				
				dt.seconds -= 60;
				dt.minutes += 1;
			}

			if(dt.seconds < 0){
				dt.seconds = 0;
				dt.dead = true;
			}
			return dt;
		}

		function niceTime(dt){
			var rip = "";
			if(dt.dead)return " rip &lt;/3";
			return dt.years + " Years, " + dt.days + " Days, " + dt.hours + " Hours, " + dt.minutes + " Minutes, " + dt.seconds + " Seconds." + rip;
		}
		/*
		$( document ).ready(function() {
			$("#cake").html("Cake");
		});
		*/
		function setData(){

			$("#data").find($(".record")).each(function(){
				var dt = detailedTime(($(this).find($(".timestamp")).first().attr("timestamp") - Math.floor(new Date() / 1000)));
				//console.log(dt);
				var value = niceTime(dt);
				$(this).find($(".cake")).html(value);
			});
		}

		var update = function update(){
			setData();
		}

		$( document ).ready(function() {

			setInterval(update, 200);


		});

	</script>

	<h1>The Final Countdown</h1>
	<div id="data">
		<table style="margin: 0 auto">
		<?php

		$times = fopen("data.csv", "r");
		$timeArray = [];

		 while (($time = fgetcsv($times)) !== FALSE) {

		 	$timeArray[$time[0]] = $time[1];
		 }

		 asort($timeArray);

		 foreach ($timeArray as $name => $timestamp) {
		 	
			?>
			
			<tr class = "record">
				<td class="tablepad"><?php print($name); ?></td>
				<td class = "cake"></td>
				<td class = "timestamp" timestamp = <?php print("'" + $timestamp + "'"); ?>></td>
			</tr>
			
			
			<?php
			
		}

		?>
		</table>
	</div>
	<h2>Delay The Inevitable</h2>
	<h2>Outlive Your Friends</h2>
	<div id="ecg"></div>

	<script type="text/javascript">

		var ecgData = [
			250,
			250,
			250,
			250,
			250,
			250,
			250,
			250,
			250,
			250,
			250,
			225,
			200,
			175,
			150,
			125,
			100,
			150,
			200,
			250,
			300,
			350,
			400,
			450,
			400,
			350,
			300,
			250,
			200,
			250,
			250,
			250,
			250,
			250,
			250,
			250,
			250
		];
		
		var svg = d3.select("#ecg")
			.append("svg")
			.attr("width", 1000)
			.attr("height", 500)
			.attr("class","ecg-svg");

		var x = d3.scaleLinear();
		var y = d3.scaleLinear();

		var i = 0;

		var line = d3.line()
    		.x(function(d) { 
    			i++;
    			return x(i*10); 
    		})
    		.y(function(d) { return y(d); });
    	var t = 0;

    	

		setInterval(function(){
			if (t >= ecgData.length){
				t = 0;
				//location.reload();
			}
			svg.select("path").remove();
	    	svg.append("path")
			      .datum(ecgData.slice(0,t))
			      .attr("class", "line")
			      .attr("d", line);
			i = 0;
			t++;
		}, 200);

	</script>

</body>
</html>