```julia

println(x < y ? "less than" : "not less than")

function test(x, y)
           if x < y
               println("x is less than y")
           elseif x > y
               println("x is greater than y")
           else
               println("x is equal to y")
           end
       end
       
z = begin
           x = 1
           y = 2
           x + y
       end

function fact(n::Int)
           n >= 0 || error("n must be non-negative")
           n == 0 && return 1
           n * fact(n-1)
       end

while i <= 5
           println(i)
           global i += 1
       end

for i = 1:5
           println(i)
       end

for s ∈ ["foo","bar","baz"]
           println(s)
       end

fussy_sqrt(x) = x >= 0 ? sqrt(x) : error("negative x not allowed")

function verbose_fussy_sqrt(x)
           println("before fussy_sqrt")
           r = fussy_sqrt(x)
           println("after fussy_sqrt")
           return r
       end

try
           sqrt("ten")
       catch e
           println("You should have entered a numeric value")
       end
```