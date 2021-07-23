const init = () => {
	//Animation variables (global because we want all scenes to run at the same frame rate).
	const targetFrameRate = 60;
	const millisecondsPerFrame = 1000 / targetFrameRate;
	let previousDeltaTime = millisecondsPerFrame;

	//Surface variables (global because we want all scenes to render to the same canvas).
	const canvas = document.getElementById("canvas");
	const ctx = canvas.getContext("2d");
	const w = canvas.width;
	const h = canvas.height;

	//Input variables (global because there's only one keyboard and one mouse).
	let keys = [];
	let mouse = { x: 0, y: 0 };
	let mouseDown = false;

	class Point {
		constructor(x, y) {
			this.x = x;
			this.y = y;
		}
	}

	//Not inheriting from Point because we don't ever want boxes to behave as points to prevent false positives on box-box collisions.
	class Box {
		constructor(x, y, w, h) {
			this.x = x;
			this.y = y;
			this.w = w;
			this.h = h;
		}
	}

	function pointCollision(point, box) {
		if (point.x < box.x) return false;
		if (point.x > box.x + box.w) return false;
		if (point.y < box.y) return false;
		if (point.y > box.y + box.h) return false;
		return true;
	}

	function boxCollision(box1, box2) {
		const b1xMin = box1.x;
		const b1xMax = box1.x + box1.w;
		const b1yMin = box1.y;
		const b1yMax = box1.y + box1.h;

		const b2xMin = box2.x;
		const b2xMax = box2.x + box2.w;
		const b2yMin = box2.y;
		const b2yMax = box2.y + box2.h;

		if (b1xMax < b2xMin) return false;	//Too farr left to collide.
		if (b1xMin > b2xMax) return false;	//Too far right to collide.
		if (b1yMax < b2yMin) return false;	//Too far up to collide.
		if (b1yMin > b2yMax) return false;	//Too far down to collide.	
		return true;
	}

	class Button extends Box {
		constructor(x, y, w, h, onClickHandler) {
			super(x, y, w, h);
			this.onClickHandler = onClickHandler;
		}

		onClick(point) {
			if (pointCollision(point, this))
				this.onClickHandler();
		}
	}

	const SceneType = {
		INVALID: -1,
		BEGIN: 0,
		MIDDLE: 1,
		END: 2
	}
	
	class Scene {
		constructor() {
			this.defaultHandlerLogging = false;
		}

		static scene = null;
		static transition(sceneType) {
			if (this.scene !== null)
				this.scene.onFinish();

			switch (sceneType) {
				case SceneType.BEGIN:
					this.scene = new BeginScene();
					break
	
				case SceneType.MIDDLE:
					this.scene = new MiddleScene();
					break
	
				case SceneType.END:
					this.scene = new EndScene();
					break

				default:
					this.scene = null;
					break
			}

			if (this.scene !== null)
				this.scene.onStart();
		}

		type() {
			return SceneType.INVALID;
		}

		onStart() {
			if (this.defaultHandlerLogging)
				console.log("Default start response: started!");
		}

		onFinish() {
			if (this.defaultHandlerLogging)
				console.log("Default finish response: finished!");
		}
	
		onUpdate(deltaTime) {
			if (this.defaultHandlerLogging)
				console.log("Default update response: " + deltaTime);
		}

		onClick(x, y) {
			if (this.defaultHandlerLogging)
				console.log("Default mouse click response: " + x + ", " + y);
		}

		onMouseMove(x, y) {
			if (this.defaultHandlerLogging)
				console.log("Default mouse move response: " + x + ", " + y);
		}

		onMouseDown(x, y) {
			if (this.defaultHandlerLogging)
				console.log("Default mouse down response: " + x + ", " + y);
		}

		onMouseUp(x, y) {
			if (this.defaultHandlerLogging)
				console.log("Default mouse up response: " + x + ", " + y);
		}

		onKeyDown(key) {
			if (this.defaultHandlerLogging)
				console.log("Default key down response:" + key);
		}

		onKeyUp(key) {
			if (this.defaultHandlerLogging)
				console.log("Default key up response: " + key);
		}
	}
	
	class BeginScene extends Scene {
		constructor() {
			super();
			this.transitionButtonColour = null;
			this.transitionButtonOverlapping = false;

			let transitionButtonWidth = 60;
			let transitionButtonHeight = 40;
			this.transitionButton = new Button(w / 2 - transitionButtonWidth / 2, h / 2 - transitionButtonHeight / 2, transitionButtonWidth, transitionButtonHeight, () => {
				Scene.transition(SceneType.MIDDLE);
			});
		}

		type() {
			return SceneType.BEGIN;
		}

		onStart() {
			alert("Begin scene starting.");
		}

		onFinish() {
			alert("Begin scene finishing.");
		}
	
		onUpdate(deltaTime) {
			//"Clear" previous frame by rendering over its entirety.
			ctx.fillRect(0, 0, w, h);
	
			//Keyboard, mouse, and overlap polling test.
			if (keys[32])
				this.transitionButtonColour = 'blue';
			else if (mouseDown)
				this.transitionButtonColour = 'green';
			else if (this.transitionButtonOverlapping)
				this.transitionButtonColour = 'cyan';
			else
				this.transitionButtonColour = 'red';

			ctx.fillStyle = this.transitionButtonColour;
			ctx.fillRect(this.transitionButton.x, this.transitionButton.y, this.transitionButton.w, this.transitionButton.h);

			ctx.fillStyle = 'white';
			ctx.fillText("Click to begin!", this.transitionButton.x, this.transitionButton.y + this.transitionButton.h / 2);
		}

		onClick(x, y) {
			this.transitionButton.onClick(new Point(x, y));
		}

		onMouseMove(x, y) {
			if (pointCollision(new Point(x, y), this.transitionButton))
				this.transitionButtonOverlapping = true;
			else
				this.transitionButtonOverlapping = false;
		}
	}

	class MiddleScene extends Scene {
		constructor() {
			super();
			this.transitionButtonColour = 'blue';
			let transitionButtonWidth = 60;
			let transitionButtonHeight = 40;
			this.transitionButton = new Button(w / 2 - transitionButtonWidth / 2, h / 2 - transitionButtonHeight / 2, transitionButtonWidth, transitionButtonHeight, () => {
				Scene.transition(SceneType.END);
			});
		}

		onStart() {
			alert("Middle scene starting.");
		}

		onFinish() {
			alert("Middle scene finishing.");
		}

		onUpdate(deltaTime) {
			ctx.fillRect(0, 0, w, h);

			ctx.fillStyle = this.transitionButtonColour;
			ctx.fillRect(this.transitionButton.x, this.transitionButton.y, this.transitionButton.w, this.transitionButton.h);

			ctx.fillStyle = 'white';
			ctx.fillText("Click to end.", 4 + this.transitionButton.x, this.transitionButton.y + this.transitionButton.h / 2);
		}

		onClick(x, y) {
			this.transitionButton.onClick(new Point(x, y));
		}
	}

	class EndScene extends Scene {
		constructor() {
			super();
			this.transitionButtonColour = 'darkgrey';
			let transitionButtonWidth = 60;
			let transitionButtonHeight = 40;
			this.transitionButton = new Button(w / 2 - transitionButtonWidth / 2, h / 2 - transitionButtonHeight / 2, transitionButtonWidth, transitionButtonHeight, () => {
				Scene.transition(SceneType.BEGIN);
			});
		}

		onStart() {
			alert("End scene starting.");
		}

		onFinish() {
			alert("End scene finishing.");
		}

		onUpdate(deltaTime) {
			ctx.fillRect(0, 0, w, h);

			ctx.fillStyle = this.transitionButtonColour;
			ctx.fillRect(this.transitionButton.x, this.transitionButton.y, this.transitionButton.w, this.transitionButton.h);

			ctx.fillStyle = 'white';
			ctx.fillText("Restart.", 10 + this.transitionButton.x, this.transitionButton.y + this.transitionButton.h / 2);
		}

		onClick(x, y) {
			this.transitionButton.onClick(new Point(x, y));
		}
	}

	//Initialize the desired first scene.
	//Note that DOM event listeners are registered *after* the scene is initialized because our handlers require a valid Scene object.
	Scene.transition(SceneType.BEGIN);

	canvas.addEventListener('click', e => {
		Scene.scene.onClick(e.offsetX, e.offsetY);
	}, false);

	canvas.addEventListener('mousemove', e => {
		mouse.x = e.offsetX;
		mouse.y = e.offsetY;
		Scene.scene.onMouseMove(e.offsetX, e.offsetY);
	});

	canvas.addEventListener('mousedown', e => {
		mouseDown = true;
		Scene.scene.onMouseDown(e.offsetX, e.offsetY);
	});

	canvas.addEventListener('mouseup', e => {
		mouseDown = false;
		Scene.scene.onMouseUp(e.offsetX, e.offsetY);
	});
	
	window.addEventListener('keydown', e => {
		keys[e.keyCode] = true;
		Scene.scene.onKeyDown(e.keyCode);
	}, false);
	
	window.addEventListener('keyup', e => {
		keys[e.keyCode] = false;
		Scene.scene.onKeyUp(e.keyCode);
	}, false);

	//timestamp is assigned internally by requestAnimationFrame. It stores the time in milliseconds since the document loaded at which requestAnimationFrame was executed.
	function gameLoop(timestamp) {
		Scene.scene.onUpdate(previousDeltaTime);
		previousDeltaTime = performance.now() - timestamp;
		setTimeout(requestAnimationFrame(gameLoop), millisecondsPerFrame - previousDeltaTime);
	}

	//Start the game (update & render) loop!
	requestAnimationFrame(gameLoop);
}