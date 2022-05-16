import 'dart:math';

void main() {
  List<int> numbers = [1, 2, 3, 4, 5, 6, 7, 8, 9, 13, 17777, 29999];
  for (int number in numbers) {
    if (isPrime(number)) {
      print("$number is prime.");
    } else {
      print("$number is not prime.");
    }
  }
}

bool isPrime(int number) {
  for (int i = 2, limit = sqrt(number).toInt(); i <= limit; i += 2) {
    if (number % i == 0) {
      return false;
    }
  }
  return true;
}