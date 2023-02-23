const image_buttons = document.querySelectorAll('.image-button');

let supportsPassive = false;
try {
  window.addEventListener("test", null, Object.defineProperty({}, 'passive', {
    get: function () { supportsPassive = true; }
  }));
} catch(e) {}

const wheelOpt = supportsPassive ? { passive: false } : false;
const wheelEvent = 'onwheel' in document.createElement('div') ? 'wheel' : 'mousewheel';

class ScrollController {
	constructor() {
		this._handler = this._handler.bind(this);
	}

	_handler(event) {
		event.preventDefault();
		event.stopPropagation();
	}

	disable() {
		window.addEventListener('DOMMouseScroll', this._handler, false); // older FF
  		window.addEventListener(wheelEvent, this._handler, wheelOpt); // modern desktop
  		window.addEventListener('touchmove', this._handler, wheelOpt); // mobile
	}

	enable() {
		window.removeEventListener('DOMMouseScroll', this._handler, false); // older FF
		window.removeEventListener(wheelEvent, this._handler, wheelOpt); // modern desktop
		window.removeEventListener('touchmove', this._handler, wheelOpt); // mobile
	}
}

const scroll_controller = new ScrollController();

image_buttons.forEach((button) => {
	button.addEventListener('click', (event) => {
		event.preventDefault();

		const button_initial_height = button.clientHeight;
		button.classList.toggle('active');

		if (button.classList.contains('active')) {
			button.style.height = `${button_initial_height}`;
			scroll_controller.disable();
		} else {
			button.style.height = 'auto';
			scroll_controller.enable();
		}
	})
})