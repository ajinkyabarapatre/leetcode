/**
 * @return {Function}
 */
var createHelloWorld = function() {
    return function() {
        return "Hello World";
    };
};
var createHelloWorld = function() {
    return function() {
        return "Hello World";
    };
};

const f = createHelloWorld();
console.log(f());           // Hello World
console.log(f(1, 2, 3));    // Hello World