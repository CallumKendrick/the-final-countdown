Pebble.addEventListener('ready', function() {

    var method = "GET";
    var url = "http://172.16.101.42/life/";

    var request = new XMLHttpRequest({name: "Callum"});

    request.open(method, url);
    request.send();

    request.onload = function() {
        var response = this.responseText;

        var dict = {
            ETD: this.response >>> 0
        };

        console.log(response);

        Pebble.sendAppMessage(dict, function() {
            console.log("sent");
        }, function(e) {
            console.log("failed");
        });
    };

});
