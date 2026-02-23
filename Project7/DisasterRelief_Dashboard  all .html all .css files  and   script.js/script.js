document.addEventListener('DOMContentLoaded', () => {
    // --- COUNTER ANIMATION ---
    const counters = document.querySelectorAll('.counter');
    const speed = 200;

    counters.forEach(counter => {
        const updateCount = () => {
            const target = +counter.getAttribute('data-target');
            const count = +counter.innerText.replace(/[^0-9.-]+/g, "");
            const inc = target / speed;

            if (count < target) {
                counter.innerText = (counter.innerHTML.includes('$') ? '$' : '') + Math.ceil(count + inc).toLocaleString();
                setTimeout(updateCount, 1);
            } else {
                counter.innerText = (counter.innerHTML.includes('$') ? '$' : '') + target.toLocaleString();
            }
        };
        updateCount();
    });

    // --- CHART INITIALIZATION ---
    const ctx = document.getElementById('mainChart');
    if (ctx) {
        new Chart(ctx, {
            type: 'line',
            data: {
                labels: ['Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat', 'Sun'],
                datasets: [{
                    label: 'Resources Dispatched',
                    data: [420, 580, 490, 820, 710, 950, 1100],
                    borderColor: '#0ea5e9',
                    backgroundColor: 'rgba(14, 165, 233, 0.1)',
                    fill: true,
                    tension: 0.4,
                    borderWidth: 3
                }]
            },
            options: {
                responsive: true,
                plugins: { legend: { display: false } },
                scales: {
                    y: { grid: { color: 'rgba(255,255,255,0.05)' }, ticks: { color: '#94a3b8' } },
                    x: { grid: { display: false }, ticks: { color: '#94a3b8' } }
                }
            }
        });
    }

    const pieCtx = document.getElementById('pieChart');
    if (pieCtx) {
        new Chart(pieCtx, {
            type: 'doughnut',
            data: {
                labels: ['High Priority', 'Moderate', 'Low'],
                datasets: [{
                    data: [45, 35, 20],
                    backgroundColor: ['#ef4444', '#f59e0b', '#10b981'],
                    borderWidth: 0,
                    hoverOffset: 10
                }]
            },
            options: {
                responsive: true,
                plugins: {
                    legend: {
                        position: 'bottom',
                        labels: { color: '#94a3b8', padding: 20 }
                    }
                },
                cutout: '70%'
            }
        });
    }
});

// Mock notification bell function
document.querySelector('.notification-bell')?.addEventListener('click', () => {
    alert("System Intelligence:\n- Low stock in Lahore-North sector.\n- New resource request from Quetta-West.\n- System tier stable.");
});

// Navigation Active State logic
const currentPath = window.location.pathname;
document.querySelectorAll('.nav-link').forEach(link => {
    if (link.getAttribute('href') && currentPath.includes(link.getAttribute('href'))) {
        link.classList.add('active');
    }
});

// --- EMERGENCY MODAL LOGIC ---
function openEmergencyModal() {
    document.getElementById('emergencyModal').style.display = 'flex';
}

function closeEmergencyModal() {
    document.getElementById('emergencyModal').style.display = 'none';
}

function submitEmergency() {
    const location = document.getElementById('em-location').value;
    const type = document.getElementById('em-type').value;
    const severity = document.querySelector('input[name="severity"]:checked').value;
    const desc = document.getElementById('em-desc').value;

    if (!location || !desc) {
        alert("Please fill in all mandatory fields (Location and Description).");
        return;
    }

    // Logic to add to the table (Simulation)
    const tableBody = document.querySelector('.table-wrapper tbody');
    if (tableBody) {
        const newRow = tableBody.insertRow(0);
        newRow.style.animation = "fadeIn 0.5s ease-out";

        const severityClass = severity === 'critical' ? 'pill-danger' : (severity === 'moderate' ? 'pill-warning' : 'pill-success');
        const severityText = severity.toUpperCase();

        newRow.innerHTML = `
            <td>${location}</td>
            <td>${type}</td>
            <td>N/A</td>
            <td><span class="status-pill ${severityClass}"><div class="dot"></div> ${severityText}</span></td>
            <td>Just now</td>
        `;
    }

    alert(`Emergency Logged Successfully!\nLocation: ${location}\nSeverity: ${severity.toUpperCase()}\nStatus: BROADCASTED`);

    // Clear and close
    document.getElementById('em-location').value = '';
    document.getElementById('em-desc').value = '';
    closeEmergencyModal();
}

// Close modal when clicking outside
window.onclick = function (event) {
    const modal = document.getElementById('emergencyModal');
    if (event.target == modal) {
        closeEmergencyModal();
    }
}
