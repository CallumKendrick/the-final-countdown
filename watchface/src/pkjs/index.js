Pebble.addEventListener('ready', function() {
  var dict = {
      ETD: 2133600000
  };

  Pebble.sendAppMessage(dict, function() {
      console.log("sent");
  }, function(e) {
      console.log("faield");
  });
});
