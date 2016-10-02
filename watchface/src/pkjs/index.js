Pebble.addEventListener('ready', function() {
  var dict = {
      ETD: 2207520000 >>> 0
  };

  Pebble.sendAppMessage(dict, function() {
      console.log("sent");
  }, function(e) {
      console.log("faield");
  });
});
