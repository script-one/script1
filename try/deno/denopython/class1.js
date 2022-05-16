import { python } from "https://deno.land/x/python/mod.ts";

const { Person } = python.runModule(`
class Person:
  def __init__(self, name):
    self.name = name
`);

const person = new Person("John");

console.log('person.name.valueOf()=', person.name.valueOf());
console.log('person.name = "Jane"');
console.log('person.name.valueOf()=', person.name.valueOf());
console.log('name in person=', "name" in person);

