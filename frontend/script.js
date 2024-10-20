document.addEventListener('DOMContentLoaded', () => {
    fetch('http://localhost:8080/api')
        .then(response => response.json())
        .then(data => {
            const productsDiv = document.getElementById('products');
            productsDiv.innerHTML = data.message;
        });
});
