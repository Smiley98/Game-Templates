const init = () => {
	let canvas = document.getElementById("canvas");
	let ctx = canvas.getContext("2d");
	let w = canvas.width;
	let h = canvas.height;
	let mouse = { x: 0, y: 0 };
	let keysDown = [];
	let fps = Math.floor(1000/60);
	let colour = 'red';
	
	function gameLoop() {
		let frameBegin = Date.now();
		
		ctx.fillStyle = 'white';
		ctx.fillRect(0, 0, w, h);
		
		if (keysDown[32])
			colour = 'blue';
		ctx.fillStyle = colour;
		ctx.fillRect(mouse.x - 20, mouse.y - 30, 40, 60);
		
		setTimeout(requestAnimationFrame(gameLoop), fps - (Date.now() - frameBegin));
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