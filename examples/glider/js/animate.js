dataset = "cartposition.csv";

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

	/* scene */ 
	var scene = new THREE.Scene();
	var camera = new THREE.PerspectiveCamera( 
		75, window.innerWidth / window.innerHeight, 0.1, 1000 );

	/* renderer */ 
	var renderer = new THREE.WebGLRenderer();
	renderer.setSize( window.innerWidth, window.innerHeight ); 
	document.body.appendChild( renderer.domElement );
	
	var time = 0;

	/* sphere geometry */ 
	var sphereGeometry = new THREE.SphereGeometry( 1 ); 
	var sphereMaterial = new THREE.MeshBasicMaterial( { color: 0x00ff00 } );
	var sphere = []; 

	for (i = 0; i < numParticles; i++) {
		sphere[i] = new THREE.Mesh( sphereGeometry, sphereMaterial); 
		scene.add(sphere[i]); 
	}

	camera.position.set(200, 0, 200); 
	camera.lookAt(0, 0, 0); 
	// var time = 0;

	var animate = function () {
		requestAnimationFrame( animate );

		for (i = 0; i < numParticles; i++) {
			sphere[i].position.x = positionData[2 * time + i].x; 
			sphere[i].position.y = positionData[2 * time + i].y; 
			sphere[i].position.z = positionData[2 * time + i].z;

		}

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
