# profiler

This C profiler is used to messure time during runtime. A quick example is [here](##Example) provided

## Example

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Copy Code Example</title>
</head>
<body>
    <pre>
        <code id="code-block">
            // Dein Code hier
            function helloWorld() {
                console.log("Hallo, Welt!");
            }
        </code>
    </pre>

    <button onclick="copyCode()">Code kopieren</button>

    <script>
        function copyCode() {
            const codeBlock = document.getElementById('code-block');
            const textArea = document.createElement('textarea');
            textArea.value = codeBlock.textContent;
            document.body.appendChild(textArea);
            textArea.select();
            document.execCommand('copy');
            document.body.removeChild(textArea);
            alert('Code wurde in die Zwischenablage kopiert!');
        }
    </script>
</body>
</html>
