/**
 * service.js
 *
 * Computer Science 50
 * Problem Set 8
 *
 * Implements a shuttle service.
 */

// default height
var HEIGHT = 0.8;

// default latitude
var LATITUDE = 42.3745615030193;

// default longitude
var LONGITUDE = -71.11803936751632;

// default heading
var HEADING = 1.757197490907891;

// default number of seats
var SEATS = 10;

// default velocity
var VELOCITY = 50;

// global reference to shuttle's marker on 2D map
var bus = null;

// global reference to 3D Earth
var earth = null;

// global reference to 2D map
var map = null;

// global reference to shuttle
var shuttle = null;

// load version 1 of the Google Earth API
google.load("earth", "1");

// load version 3 of the Google Maps API
google.load("maps", "3", {other_params: "sensor=false"});

// once the window has loaded
$(window).load(function() {

    // listen for keydown anywhere in body
    $(document.body).keydown(function(event) {
        return keystroke(event, true);
    });

    // listen for keyup anywhere in body
    $(document.body).keyup(function(event) {
        return keystroke(event, false);
    });

    // listen for click on Drop Off button
    $("#dropoff").click(function(event) {
        dropoff();
    });

    // listen for click on Pick Up button
    $("#pickup").click(function(event) {
        pickup();
    });

    // load application
    load();
});

// unload application
$(window).unload(function() {
    unload();
});

/**
 * Renders seating chart.
 */
function chart()
{
    var html = "<ol start='0'>";
    for (var i = 0; i < shuttle.seats.length; i++)
    {
        if (shuttle.seats[i] == null)
        {
            html += "<li>Empty Seat</li>";
        }
        else
        {
            html += "<li>" + "TODO" + "</li>";
        }
    }
    html += "</ol>";
    $("#chart").html(html);
}

/**
 * Drops up passengers if their stop is nearby.
 */
function dropoff()
{
	var div, txt;
	if (!(passengers.length)) {
		if (!document.getElementById('nopassengers')) {
			document.getElementById('noannouncements').style.display='none';
			div=document.createElement('div');
			div.setAttribute('id', 'nopassengers');
			txt=document.createTextNode('You don\'t have any passengers.');
			div.appendChild(txt);
			document.getElementById('announcements').appendChild(div);
			setTimeout("expire_announcement('nopassengers')",4000);
		}
		return;
	}

	var droppedOff = false;
	//loop through all people currently aboard, in a reverse order,
	// so we can use splice in-place to remove passengers
	for (var index = passengers.length - 1; index >= 0; index--) {
		var passenger = passengers[index];
		var housename = passenger.house;
		var house = HOUSES[housename];
		//alert(house.lat);
		//break;
		//the distance bettween where the bus currently is and the passenger's destination
		var d = shuttle.distance(house.lat, house.lng);
		if (d < 30.0) {
			//drop off this passenger
			//the 'seat' the passenger is on (actually just in respect to the sorted list of seats)
			var seat = document.getElementById('bus_' + passenger.username);
			//change it back to empty seat
			seat.firstChild.data = "Empty Seat";
			//clears the id=value pair from the seat
			seat.removeAttribute('id');

			//construct and post the announcement
			document.getElementById('noannouncements').style.display='none';
			div=document.createElement('div');
			div.setAttribute('id', 'dropped_' + passenger.username);
			txt=document.createTextNode('Dropped off ' + passenger.name);
			div.appendChild(txt);
			document.getElementById('announcements').appendChild(div);
			//this announced message will self-distruct in 4 seconds
			//we're leveraging the fact that all 'usernames' are simple alphanumeric strings without weird chars
			setTimeout("expire_announcement('dropped_" + passenger.username + "')",4000);
			//remove pasenger from passengers.
			passengers.splice(index,1);
			droppedOff = true;
		}
	}
	if (!(droppedOff)) {
		if (!document.getElementById('nodropoff')) {
			document.getElementById('noannouncements').style.display='none';
			div=document.createElement('div');
			div.setAttribute('id', 'nodropoff');
			txt=document.createTextNode('No passengers want to drop off here.');
			div.appendChild(txt);
			document.getElementById('announcements').appendChild(div);
			setTimeout("expire_announcement('nodropoff')",4000);
		}
	}
}


/**
 * Called if Google Earth fails to load.
 */
function failureCB(errorCode) 
{
    // report error unless plugin simply isn't installed
    if (errorCode != ERR_CREATE_PLUGIN)
    {
        alert(errorCode);
    }
}

/**
 * Handler for Earth's frameend event.
 */
function frameend() 
{
    shuttle.update();
}

/**
 * Called once Google Earth has loaded.
 */
function initCB(instance) 
{
    // retain reference to GEPlugin instance
    earth = instance;

    // specify the speed at which the camera moves
    earth.getOptions().setFlyToSpeed(100);

    // show buildings
    earth.getLayerRoot().enableLayerById(earth.LAYER_BUILDINGS, true);

    // disable terrain (so that Earth is flat)
    earth.getLayerRoot().enableLayerById(earth.LAYER_TERRAIN, false);

    // prevent mouse navigation in the plugin
    earth.getOptions().setMouseNavigationEnabled(false);

    // instantiate shuttle
    shuttle = new Shuttle({
        heading: HEADING,
        height: HEIGHT,
        latitude: LATITUDE,
        longitude: LONGITUDE,
        planet: earth,
        seats: SEATS,
        velocity: VELOCITY
    });

    // synchronize camera with Earth
    google.earth.addEventListener(earth, "frameend", frameend);

    // synchronize map with Earth
    google.earth.addEventListener(earth.getView(), "viewchange", viewchange);

    // update shuttle's camera
    shuttle.updateCamera();

    // show Earth
    earth.getWindow().setVisibility(true);

    // render seating chart
    chart();

    // populate Earth with passengers and houses
    populate();
}

/**
 * Handles keystrokes.
 */
function keystroke(event, state)
{
    // ensure we have event
    if (!event)
    {
        event = window.event;
    }

    // left arrow
    if (event.keyCode == 37)
    {
        shuttle.states.turningLeftward = state;
        return false;
    }

    // up arrow
    else if (event.keyCode == 38)
    {
        shuttle.states.tiltingUpward = state;
        return false;
    }

    // right arrow
    else if (event.keyCode == 39)
    {
        shuttle.states.turningRightward = state;
        return false;
    }

    // down arrow
    else if (event.keyCode == 40)
    {
        shuttle.states.tiltingDownward = state;
        return false;
    }

    // A, a
    else if (event.keyCode == 65 || event.keyCode == 97)
    {
        shuttle.states.slidingLeftward = state;
        return false;
    }

    // D, d
    else if (event.keyCode == 68 || event.keyCode == 100)
    {
        shuttle.states.slidingRightward = state;
        return false;
    }
  
    // S, s
    else if (event.keyCode == 83 || event.keyCode == 115)
    {
        shuttle.states.movingBackward = state;     
        return false;
    }

    // W, w
    else if (event.keyCode == 87 || event.keyCode == 119)
    {
        shuttle.states.movingForward = state;    
        return false;
    }
  
    return true;
}

/**
 * Loads application.
 */
function load()
{
    // embed 2D map in DOM
    var latlng = new google.maps.LatLng(LATITUDE, LONGITUDE);
    map = new google.maps.Map($("#map").get(0), {
        center: latlng,
        disableDefaultUI: true,
        mapTypeId: google.maps.MapTypeId.ROADMAP,
        scrollwheel: false,
        zoom: 17,
        zoomControl: true
    });

    // prepare shuttle's icon for map
    bus = new google.maps.Marker({
        icon: "https://maps.gstatic.com/intl/en_us/mapfiles/ms/micons/bus.png",
        map: map,
        title: "you are here"
    });

    // embed 3D Earth in DOM
    google.earth.createInstance("earth", initCB, failureCB);
}

/**
 * Picks up nearby passengers.
 */
function pickup() {
	var NewPassengers = new Array();
	var div, txt;
	var pickedUp = false;
	//loop through all people still on the map
	for (var index = 0; index < people.length; index++) {
		// local reference for a repaining person on the map
		var passenger = people[index];
		//how far is the 'bus' from the passenger?
		var d = shuttle.distance(passenger.lat, passenger.lng);
		//check if the person is within 15 meters of the bus
		if (d < 15.0) {
			//look for an empty seat
			var seat = find_empty_seat();
			if (seat == -1) {
				//Bus is full. inform the user and abort
				document.getElementById('noannouncements').style.display='none';
				div=document.createElement('div');
				div.setAttribute('id', 'shuttle_full');
				txt=document.createTextNode('The CS50 Shuttle is full!');
				div.appendChild(txt);
				document.getElementById('announcements').appendChild(div);
				setTimeout("expire_announcement('shuttle_full')",4000);
				break;
			}
			//remove this passenger from google earth
			earth.getFeatures().removeChild(passenger.placemark);
			//remove this passenger from 2D google maps
			passenger.marker.setMap(null);
			//announce the action
			document.getElementById('noannouncements').style.display='none';
			//http://www.webmasterworld.com/javascript/3157922.htm
			div=document.createElement('div');
			div.setAttribute('id', 'boarded_' + passenger.username);
			txt=document.createTextNode('Picked up ' + passenger.name);
			div.appendChild(txt);
			document.getElementById('announcements').appendChild(div);
			//this announced message will self-distruct in 4 seconds
			//we're leveraging the fact that all 'usernames' are simple alphanumeric strings without weird chars
			setTimeout("expire_announcement('boarded_" + passenger.username + "')",4000);
			//add passenger to seat
			var allSeats = document.getElementById('seats').getElementsByTagName('li');
			allSeats[seat].setAttribute('id', 'bus_' + passenger.username);
			allSeats[seat].firstChild.data = passenger.name + " to " + passenger.house;

			// array we will later use to remove people from people[] with splice
			NewPassengers.unshift(index); // LIFO !
			pickedUp = true;
		}
	}
	for (var i = 0; i < NewPassengers.length; i++) {
		var peopleIndex = NewPassengers[i];
		passengers.push( people[ peopleIndex ]);
		people.splice( peopleIndex,1);
	}
	if (!(pickedUp)) {
		if (!document.getElementById('nopickup')) {
			document.getElementById('noannouncements').style.display='none';
			div=document.createElement('div');
			div.setAttribute('id', 'nopickup');
			txt=document.createTextNode('No one around here.');
			div.appendChild(txt);
			document.getElementById('announcements').appendChild(div);
			setTimeout("expire_announcement('nopickup')",4000);
		}
	}
}


/**
 * Populates Earth with passengers and houses.
 */
function populate()
{
    // mark houses
    for (var house in HOUSES)
    {
        // plant house on map
        new google.maps.Marker({
            icon: "https://google-maps-icons.googlecode.com/files/home.png",
            map: map,
            position: new google.maps.LatLng(HOUSES[house].lat, HOUSES[house].lng),
            title: house
        });
    }

    // get current URL, sans any filename
    var url = window.location.href.substring(0, (window.location.href.lastIndexOf("/")) + 1);

    // scatter passengers
    for (var i = 0; i < PASSENGERS.length; i++)
    {
        // pick a random building
        var building = BUILDINGS[Math.floor(Math.random() * BUILDINGS.length)];

        // prepare placemark
        var placemark = earth.createPlacemark("");
        placemark.setName(PASSENGERS[i].name + " to " + PASSENGERS[i].house);

        // prepare icon
        var icon = earth.createIcon("");
        icon.setHref(url + "/img/" + PASSENGERS[i].username + ".jpg");

        // prepare style
        var style = earth.createStyle("");
        style.getIconStyle().setIcon(icon);
        style.getIconStyle().setScale(4.0);

        // prepare stylemap
        var styleMap = earth.createStyleMap("");
        styleMap.setNormalStyle(style);
        styleMap.setHighlightStyle(style);

        // associate stylemap with placemark
        placemark.setStyleSelector(styleMap);

        // prepare point
        var point = earth.createPoint("");
        point.setAltitudeMode(earth.ALTITUDE_RELATIVE_TO_GROUND);
        point.setLatitude(building.lat);
        point.setLongitude(building.lng);
        point.setAltitude(0.0);

		// associate placemark with point
		placemark.setGeometry(point);

		// add placemark to Earth
		earth.getFeatures().appendChild(placemark);

		//add this passenger's location to an array for later use.
		//person[ PASSENGERS[i].username ] = { lat: building.lat, lng: building.lng, i:i };
		people[i] = PASSENGERS[i];
		people[i].lat = building.lat;
		people[i].lng = building.lng;
		people[i].placemark = placemark;

		// add marker to map
		var marker = new google.maps.Marker({
			icon: "http://maps.gstatic.com/intl/en_us/mapfiles/ms/micons/man.png",
			map: map,
			position: new google.maps.LatLng(building.lat, building.lng),
			title: PASSENGERS[i].name + " at " + building.name
		});
		people[i].marker = marker;
	//people[i].isonbus = false; // superfluous logic
	}
}

/**
 * Handler for Earth's viewchange event.
 */
function viewchange() 
{
    // keep map centered on shuttle's marker
    var latlng = new google.maps.LatLng(shuttle.position.latitude, shuttle.position.longitude);
    map.setCenter(latlng);
    bus.setPosition(latlng);
}

/**
 * Unloads Earth.
 */
function unload()
{
    google.earth.removeEventListener(earth.getView(), "viewchange", viewchange);
    google.earth.removeEventListener(earth, "frameend", frameend);
}