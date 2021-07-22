const init = () => {
	//Animation variables.
	const targetFrameRate = 60;
	const millisecondsPerFrame = 1000 / targetFrameRate;
	let deltaTime = millisecondsPerFrame;

	//Surface variables.
	let canvas = document.getElementById("canvas");
	let ctx = canvas.getContext("2d");
	let w = canvas.width;
	let h = canvas.height;

	//Input variables.
	let mouse = { x: 0, y: 0 };
	let keysDown = [];
	let colour = 'red';
	
	//timestamp is assigned internally by requestAnimationFrame. It stores the time in milliseconds since the document loaded at which requestAnimationFrame was executed.
	function gameLoop(timestamp) {
		//"Clear" previous frame by rendering over its entirety.
		ctx.fillStyle = 'white';
		ctx.fillRect(0, 0, w, h);
		
		//Keyboard and mouse test.
		if (keysDown[32])
			colour = 'blue';
		ctx.fillStyle = colour;
		ctx.fillRect(mouse.x - 20, mouse.y - 30, 40, 60);

		//Update timers and restart issue a request to render the pending frame.
		deltaTime = performance.now() - timestamp;
		setTimeout(requestAnimationFrame(gameLoop), millisecondsPerFrame - deltaTime);
	}
	requestAnimationFrame(gameLoop);

	canvas.addEventListener('mousemove', e => {
		mouse.x = e.offsetX;
		mouse.y = e.offsetY;
	});

	canvas.addEventListener('mousedown', e => {
		colour = 'green';
	});

	canvas.addEventListener('mouseup', e => {
		colour = 'red';
	});
	
	canvas.addEventListener('click', e => {
		console.log("Click!");
	}, false);
	
	window.addEventListener('keydown', e => {
		var keyDown = e.keyCode;
		keysDown[keyDown] = true;
	}, false);
	
	window.addEventListener('keyup', e => {
		var keyUp = e.keyCode;
		keysDown[keyUp] = false;
	}, false);
}