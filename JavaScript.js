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

		onClick() {
			console.log("Click!");
		}

		onMouseMove(x, y) {
			console.log("Mouse move!");
		}

		onMouseDown() {
			console.log("Mouse down!");
		}

		onMouseUp() {
			console.log("Mouse up!");
		}

		onKeyDown(key) {
			console.log("Key down!");
		}

		onKeyUp(key) {
			console.log("Key up!");
		}
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

	canvas.addEventListener('click', e => {
		scene.onClick();
	}, false);

	canvas.addEventListener('mousemove', e => {
		let x = e.offsetX;
		let y = e.offsetY;
		mouse.x = x;
		mouse.y = y;
		scene.onMouseMove(x, y);
	});

	canvas.addEventListener('mousedown', e => {
		scene.onMouseDown();
	});

	canvas.addEventListener('mouseup', e => {
		scene.onMouseUp();
	});
	
	window.addEventListener('keydown', e => {
		var keyDown = e.keyCode;
		keys[keyDown] = true;
		scene.onKeyDown(keyDown);
	}, false);
	
	window.addEventListener('keyup', e => {
		var keyUp = e.keyCode;
		keys[keyUp] = false;
		scene.onKeyUp(keyUp);
	}, false);
}