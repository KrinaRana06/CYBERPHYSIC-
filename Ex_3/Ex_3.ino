float num1, num2;
char op;

void setup() {
  Serial.begin(9600);
  Serial.println("Enter: number operator number (Example: 8 * 5)");
}

void loop() {
  if (Serial.available() > 0) {

    String input = Serial.readStringUntil('\n');

    Serial.print("Received: ");
    Serial.println(input);

    // operator position is  manual
    int pos;
    if (input.indexOf('+') > 0) {
      op = '+';
      pos = input.indexOf('+');
    } else if (input.indexOf('-') > 0) {
      op = '-';
      pos = input.indexOf('-');
    } else if (input.indexOf('*') > 0) {
      op = '*';
      pos = input.indexOf('*');
    } else if (input.indexOf('/') > 0) {
      op = '/';
      pos = input.indexOf('/');
    } else {
      Serial.println("Invalid operator! Use + - * /");
      return;
    }

    // Split the input into two number substrings
    String part1 = input.substring(0, pos);
    String part2 = input.substring(pos + 1);

    num1 = part1.toFloat();
    num2 = part2.toFloat();

    float result = 0;

    if (op == '+') result = num1 + num2;
    else if (op == '-') result = num1 - num2;
    else if (op == '*') result = num1 * num2;
    else if (op == '/') {
      if (num2 != 0) result = num1 / num2;
      else {
        Serial.println("Error: Division by zero!");
        return;
      }
    }

    Serial.print("Result: ");
    Serial.println(result);
    Serial.println("Enter: number operator number (Example: 8 * 5)");
  }
}
