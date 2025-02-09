### Magnum opus computer architecture implemented in C++

We need Visualization (pretty printing)
A computer interface (pretty printing?)

Start with basic logic gates, by following Turing complete.

We represent a full circuit (meta-class?) with a user or later a stack input and a console output.
You can add components and connect them among each other.
Each component is its own struct with inputs and outputs and some computation happening within.
One important point is that we should be able to create components from circuits by converting user/stack input and console output to component input and outputs! (we can try doing it without by simply creating a circuit for testing and then recreating it as a struct (more work less thinking?))


