const init = () => {
	var canvas = document.getElementById("canvas");
	var ctx = canvas.getContext("2d");
	var w = canvas.width;
	var h = canvas.height;
	var canvasEdges = canvas.getBoundingClientRect();
	var mx, my;
	var keysDown = [];
	var fps = Math.floor(1000/60);
	var now, then, delta;
	
	function gameLoop(){
		now=Date.now();
		ctx.clearRect(0,0,w,h);
		ctx.fillStyle='white';	//change colour
		ctx.fillRect(0,0,w,h);	//draw rectangle
		
		//code goes here
		ctx.fillStyle='red';
		if(keysDown[32])
			ctx.fillStyle='green';
		ctx.fillRect(w/2,h/2,12,48);
		console.log(mx);
		console.log(my);
		
		then=Date.now();
		delta=then-now;
		setTimeout(requestAnimationFrame(gameLoop), fps-delta);
	}
	requestAnimationFrame(gameLoop);
	
	canvas.addEventListener('click', function (evt) {
		//console.log("Click!");
	}, false);

	canvas.addEventListener('mousemove', function(evt) {
		//console.log("Aids!");
		getMousePos(canvas, evt);
	}, false);
	
	window.addEventListener('keydown', function(evt) {
		var keyDown = evt.keyCode;
		keysDown[keyDown]=true;
	}, false);
	
	window.addEventListener('keyup', function(evt) {
		var keyUp = evt.keyCode;
		keysDown[keyUp]=false;
	}, false);
	
	function getMousePos(canvas, evt) {
		//console.log(evt.clientX);
		mx = evt.clientX - canvasEdges.left;
		my = evt.clientY - canvasEdges.top;
	}
	
}