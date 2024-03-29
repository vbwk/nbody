dataset = "trajectories.csv";

var positionData;
var numParticles; 
var numTimePoints; 

d3.csv(dataset, function(d) {
	return {
		x : +d.x, 
		y : +d.y, 
		z : +d.z,
		mass : +d.mass,
		particle: d.particle
	};
}).then(function(data) {
	positionData = data;
	var numRows = d3.selectAll(data).size();

	numTimePoints = 0; 
	for (i = 0; i < numRows; i++) {
		if (positionData[i].particle == "m1") {
			numTimePoints += 1; 
		}
	}

	numParticles = numRows / numTimePoints; 
	renderAnimation();
}); 

function renderAnimation() {
	var scene = new THREE.Scene();
	var camera = new THREE.PerspectiveCamera( 
		75, window.innerWidth / window.innerHeight, 0.1, 1000 );

	var renderer = new THREE.WebGLRenderer();
	renderer.setSize( window.innerWidth, window.innerHeight ); 
	document.body.appendChild( renderer.domElement );

	var geometry = new THREE.SphereGeometry( 0.1 ); 
	var material = new THREE.MeshBasicMaterial( { color: 0x00ff00 } );
	var sphere = []; 

	for (i = 0; i < numParticles; i++) {
		sphere[i] = new THREE.Mesh( geometry, material); 
		scene.add(sphere[i]); 
	}

	/*
	var material = new THREE.LineBasicMaterial( { color: 0xffffff } );
	var linegeometry = new THREE.Geometry();

	linegeometry.vertices.push( new THREE.Vector3( 0, 0, 0) ); 
	linegeometry.vertices.push( new THREE.Vector3( 1, 0, 0) ); 

	var line = []; 

	for (i = 0; i < numParticles; i++) {
		line[i] = new THREE.Line( linegeometry, material ); 
		scene.add(line[i]); 
	}
*/ 

	camera.position.set(0, 0, -7); 
	camera.lookAt(0, 0, 0); 
	var time = 0;

	var animate = function () {
		requestAnimationFrame( animate );

		for (i = 0; i < numParticles; i++) {
			sphere[i].position.x = positionData[2 * time + i].x; 
			sphere[i].position.y = positionData[2 * time + i].y; 
			sphere[i].position.z = positionData[2 * time + i].z;
		}

		/*
		for (i = 0; i < 1; i++) {
			linegeometry.vertices.push( new THREE.Vector3 ( 0, 0, 0) ); 
			linegeometry.vertices.push( new THREE.Vector3 (
				positionData[2 * time + 0].x, positionData[2 * time + 0].y, 
				positionData[2 * time + 0].z) );
				linegeometry.verticesNeedUpdate = true; 
		}
*/ 

		
		renderer.render( scene, camera );

		if (time < (numTimePoints - 1)) { 
			time += 1; 
		}
		else { 
			time = 0; 
		}
	}; 

	animate(); 
}
