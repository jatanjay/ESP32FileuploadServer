
// document.addEventListener('DOMContentLoaded', function () {
//     var onButton = document.getElementById('onButton');

//     onButton.addEventListener('click', function () {
//         fetch('/on')
//             .then(response => {
//                 if (!response.ok) {
//                     throw new Error('Network response was not ok');
//                 }
//                 return response.text();
//             })
//             .then(data => {
//                 console.log('Response from server:', data);
//             })
//             .catch(error => {
//                 console.error('There was a problem with the fetch operation:', error);
//             });
//     });
// });


// app.js

document.addEventListener('DOMContentLoaded', function () {
    var onButton = document.getElementById('onButton');
    var waveformTypeSelect = document.getElementById('waveform-type');

    onButton.addEventListener('click', function () {
        var selectedOption = waveformTypeSelect.value;
        
        var waveformNames = {
            '1': 'Demo Mode BP',
            '2': 'Arrhythmia',
            '3': 'Arrhythmia2',
            '4': 'Fluids',
            '5': 'Ephedrine',
            '6': 'Norepi',
            '7': 'Norepi-Arth',
            '8': 'Phenylephrine',
        };

        var selectedWaveform = waveformNames[selectedOption];
        
        var url = '/' + selectedOption;

        fetch("/on")
            .then(response => {
                if (!response.ok) {
                    throw new Error('Network response was not ok');
                }
                return response.text();
            })
            .then(data => {
                console.log('Response from server:', data);
                console.log('Selected waveform:', selectedWaveform);
            })
            .catch(error => {
                console.error('There was a problem with the fetch operation:', error);
            });
    });
});
