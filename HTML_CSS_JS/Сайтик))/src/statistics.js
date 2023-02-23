const template = (index) => ({
	age: index,
	days: index * 365,
	sleep_hours: index * 365 * 8
})
const data = Array.from(Array(40), (_, index) => index).map(template);

const colors = [
	'rgb(75, 192, 192)',
	'rgb(255,162,00)'
];


var ctx = document.getElementById('myChart').getContext('2d');
var myChart = new Chart(ctx, {
	type: 'line',
	data: {
		backgroundColor: 'rgb(ff, 66, 00)',
		labels: data.map(data => data.age),
		datasets: [
			{
				label: 'Прожитые дни',
				data: data.map(item => item.days),
				fill: false,
				borderColor: colors[0],
				tension: 0.1
			},
			{
				label: 'Часы сна',
				data: data.map(item => item.sleep_hours),
				fill: false,
				borderColor: colors[1],
				tension: 0.1
			},
		]
	},
	options: {
		scales: {
			y: {
				beginAtZero: true
			}
		}
	}

});

function get_random_color() {
	const r = Math.floor(Math.random() * 255);
	const g = Math.floor(Math.random() * 255);
	const b = Math.floor(Math.random() * 255);
	return `rgb(${r}, ${g}, ${b})`
}

const change_colors = () => {
	colors[0] = get_random_color();
	colors[1] = get_random_color();

	myChart.data.datasets[0].borderColor = colors[0];
	myChart.data.datasets[1].borderColor = colors[1];
	myChart.update()
};