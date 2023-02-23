const get_notes = () => Array.from(document.querySelectorAll('.note'))
	.filter((note) => !('ghost' in note.dataset));
const ghost_note = document.querySelector('.note[data-ghost]');

const is_touch_device = 'ontouchstart' in window;

const initial_coords = {
	x: 0,
	y: 0
};

const initial_note_coords = {
	x: 0,
	y: 0
}

const current_coords = {
	x: 0,
	y: 0
};

const NativeEventName = {
	Start: is_touch_device ? 'touchstart' : 'mousedown',
	Move: is_touch_device ? 'touchmove' : 'mousemove',
	End : is_touch_device ? 'touchend' : 'mouseup'
};

function hide_original_note(note) {
	note.dataset.hidden = true;
}

function show_original_note(note) {
	note.removeAttribute('data-hidden');
}

function get_coordinates(event) {
	if (is_touch_device) {
		return {
			x: parseInt(event.touches[0].clientX),
			y: parseInt(event.touches[0].clientY)
		};
	} else {
		return {
			x: parseInt(event.clientX),
			y: parseInt(event.clientY)
		};
	}
}

function copy_content_to_ghost(target_note) {
	ghost_note.innerHTML = target_note.innerHTML;
}

function clear_ghost_content() {
	ghost_note.innerHTML = '';
}

function reveal_ghost_note(coords, size) {
	ghost_note.dataset.visible = true;
	ghost_note.style = `top: ${coords.y}px; left: ${coords.x}px; width: ${size.width}px; height: ${size.height}px`;
}

function hide_ghost_node() {
	ghost_note.removeAttribute('data-visible');
	ghost_note.style = ``;
}

function handle_note_interaction(event) {
	const note = event.currentTarget;
	const coords = get_coordinates(event);
	const size = {width: note.clientWidth, height: note.clientHeight};

	initial_coords.x = parseInt(coords.x);
	initial_coords.y = parseInt(coords.y);

	const {left: x, top: y} = note.getBoundingClientRect();
	initial_note_coords.x = parseInt(x);
	initial_note_coords.y = parseInt(y);

	hide_original_note(note);
	copy_content_to_ghost(note);
	reveal_ghost_note(initial_note_coords, size);
	window.addEventListener(NativeEventName.End, handle_note_release);
	window.addEventListener(NativeEventName.Move, handle_note_drag);
}

function handle_note_drag(event) {
	const coords = get_coordinates(event);
	const dX = coords.x - initial_coords.x;
	const dY = coords.y - initial_coords.y;

	const visual_coords = {
		x: initial_note_coords.x + dX,
		y: initial_note_coords.y + dY
	};

	ghost_note.style.top = `${visual_coords.y}px`
	ghost_note.style.left = `${visual_coords.x}px`;
}

function handle_note_release(event) {
	const notes = get_notes();
	const ghost = event.currentTarget;
	const original_note = notes.find(note => 'hidden' in note.dataset);
	hide_ghost_node();
	clear_ghost_content();
	show_original_note(original_note);

	if (is_touch_device) {
		event = {
			...event,
			touches: event.changedTouches
		}
	};

	const coords = get_coordinates(event);

	const order_notes = notes;
	if (order_notes[0].getBoundingClientRect().top > coords.y) {
		order_notes[0].insertAdjacentElement('beforebegin', original_note);
	} else if (order_notes[notes.length - 1].getBoundingClientRect().top < coords.y) {
		order_notes[notes.length - 1].insertAdjacentElement('afterend', original_note);
	} else {
		const insert_after = notes.find((note, index) => {
			const next_note = notes[index + 1];
			if (!next_note) return;

			const rect = note.getBoundingClientRect();
			const next_rect = next_note.getBoundingClientRect();

			const note_center = rect.top + rect.height;
			const next_note_center = next_rect.top + next_rect.height;

			return note_center < coords.y && next_note_center > coords.y;
		});

		if(!insert_after) return;

		insert_after.insertAdjacentElement('afterend', original_note);
	}

	original_note.scrollIntoView({block: 'center'});


	window.removeEventListener(NativeEventName.Move, handle_note_drag);
	window.removeEventListener(NativeEventName.End, handle_note_release);
}

get_notes().forEach((note) => {
	note.addEventListener(NativeEventName.Start, handle_note_interaction);
});
