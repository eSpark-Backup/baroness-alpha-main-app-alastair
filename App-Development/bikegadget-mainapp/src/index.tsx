const BikegadgetMainapp = require('./NativeBikegadgetMainapp').default;

export function multiply(a: number, b: number): number {
  return BikegadgetMainapp.multiply(a, b);
}

export function install(): boolean {
  return BikegadgetMainapp.install();
}

declare function helloWorld(): string;
declare function foo(callback: (error: any, result: string) => void): void;

export function HelloWorld(): string {
  return helloWorld();
}