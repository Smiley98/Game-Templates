const init = () => {
	//Animation variables.
	const targetFrameRate = 60;
	const millisecondsPerFrame = 1000 / targetFrameRate;
	let previousDeltaTime = millisecondsPerFrame;

	//Surface variables.
	const canvas = document.getElementById("canvas");
	const ctx = canvas.getContext("2d");
	const w = canvas.width;
	const h = canvas.height;

	//Input variables.
	let mouse = { x: 0, y: 0 };
	let keys = [];

	const SceneType = {
		invalid: -1,
		main: 0,
		keyboard: 1,
		mouse: 2
	}
	
	class Scene {
		constructor() {}

		type() {
			return SceneType.invalid;
		}
	
		onUpdate(deltaTime) {}
		onKeyDown(key) {}
		onKeyUp(key) {}
		onMouseMove(x, y) {}
		onMouseDown() {}
		onMouseUp() {}
		onClick() {}
	}
	
	class MainScene extends Scene {
		constructor() {
			super();
			this.colour = 'red';
		}
	
		onUpdate(deltaTime) {
			//"Clear" previous frame by rendering over its entirety.
			ctx.fillStyle = 'white';
			ctx.fillRect(0, 0, w, h);
	
			//Keyboard and mouse test.
			if (keys[32])
				this.colour = 'blue';
			ctx.fillStyle = this.colour;
			ctx.fillRect(mouse.x - 20, mouse.y - 30, 40, 60);
			ctx.fillText(deltaTime, 100, 100);
		}
	}

	//Game variables.
	let mainScene = new MainScene();
	let scene = mainScene;
	
	//timestamp is assigned internally by requestAnimationFrame. It stores the time in milliseconds since the document loaded at which requestAnimationFrame was executed.
	function gameLoop(timestamp) {
		scene.onUpdate(previousDeltaTime);
		previousDeltaTime = performance.now() - timestamp;
		setTimeout(requestAnimationFrame(gameLoop), millisecondsPerFrame - previousDeltaTime);
	}
	requestAnimationFrame(gameLoop);

	canvas.addEventListener('mousemove', e => {
		mouse.x = e.offsetX;
		mouse.y = e.offsetY;
	});

	canvas.addEventListener('mousedown', e => {
		console.log("Mouse down!");
	});

	canvas.addEventListener('mouseup', e => {
		console.log("Mouse up!");
	});
	
	canvas.addEventListener('click', e => {
		console.log("Click!");
	}, false);
	
	window.addEventListener('keydown', e => {
		var keyDown = e.keyCode;
		keys[keyDown] = true;
	}, false);
	
	window.addEventListener('keyup', e => {
		var keyUp = e.keyCode;
		keys[keyUp] = false;
	}, false);
}