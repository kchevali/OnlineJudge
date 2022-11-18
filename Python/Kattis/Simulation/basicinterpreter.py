
from typing import  Dict, List, Union
from math import ceil, floor
# from sys import stderr

# def debug_print(*args:Any) -> None:
#     print(*args, file=stderr)

def to_int32(val:int) -> int:
    val &= ((1<<32)-1)
    if val & (1<<31): val -= (1<<32)
    return val

class Value:
    def __init__(self, value:int=0) -> None:
        self.value: int = value
    
    def assign(self, value:int) -> None:
        self.value = value

    def __str__(self) ->  str:
        return str(self.value)

class Line:
    def eval(self) -> Union[int, bool, None , 'Statement']:
        return 0

class Arithmetic(Line):
    def __init__(self, a:Value) -> None:
        self.a: Value = a
    
    def eval(self) -> int:
        return 0

class Constant(Arithmetic):
    def eval(self) -> int:
        return self.a.value

class ArithmeticOperation(Arithmetic):
    def __init__(self, a:Value, b:Value) -> None:
        super().__init__(a)
        self.b: Value = b

class Addition(ArithmeticOperation):
    def eval(self) -> int:
        return to_int32(self.a.value + self.b.value)

class Subtraction(ArithmeticOperation):
    def eval(self) -> int:
        return to_int32(self.a.value - self.b.value)

class Multiplication(ArithmeticOperation):
    def eval(self) -> int:
        return to_int32(self.a.value * self.b.value)

class Division(ArithmeticOperation):
    def eval(self) -> int:
        result: float = self.a.value / self.b.value
        return to_int32(ceil(result) if result < 0 else floor(result))

class Conditional(Line):
    def __init__(self, a:Value, b:Value) -> None:
        self.a: Value = a
        self.b: Value = b
    
    def eval(self) -> bool:
        return False

class Equal(Conditional):
    def eval(self) -> bool:
        return self.a.value == self.b.value

class LessThan(Conditional):
    def eval(self) -> bool:
        return self.a.value < self.b.value

class GreaterThan(Conditional):
    def eval(self) -> bool:
        return self.a.value > self.b.value

class NotEqual(Conditional):
    def eval(self) -> bool:
        return self.a.value != self.b.value

class LessEqual(Conditional):
    def eval(self) -> bool:
        return self.a.value <= self.b.value

class GreaterEqual(Conditional):
    def eval(self) -> bool:
        return self.a.value >= self.b.value 

class Statement(Line):
    next:Union['Statement', None] = None
    alt:Union['Statement', None] = None
    label_num: int = -1
    def __init__(self, line_num:int) -> None:
        self.line_num: int = line_num

    def eval(self) -> Union['Statement', None]:
        return None

class Assignment(Statement):
    def __init__(self, line_num:int, value:Value, arithmetic:Arithmetic) -> None:
        super().__init__(line_num)
        self.value: Value = value
        self.arithmetic: Arithmetic = arithmetic
    
    def eval(self) -> Union[Statement, None]:
        self.value.assign(self.arithmetic.eval())
        return self.next
    
class If(Statement):
    def __init__(self, line_num:int, condition:Conditional, label_num:int) -> None:
        super().__init__(line_num)
        self.condition: Conditional = condition
        self.label_num: int = label_num
    
    def eval(self) -> Union[Statement, None]:
        return self.alt if self.condition.eval() else self.next

class PrintStatement(Statement):
    buffer:List[str] = []
    line: List[str] = []
    def __init__(self, line_num:int, value:Union[str, Value]) -> None:
        super().__init__(line_num)
        self.value: Union[str, Value] = value
    
    def eval(self) -> Union[Statement, None]:
        PrintStatement.line.append(str(self.value))
        return self.next

class PrintLineStatement(PrintStatement):
    def eval(self) -> Union[Statement, None]:
        PrintStatement.line.append(str(self.value))
        PrintStatement.buffer.append("".join(PrintStatement.line))
        PrintStatement.line = []
        return self.next

def get_value(variables:Dict[str, Value], val:str) -> Value:
    if val.lstrip("-").isdigit(): return Value(int(val))
    if val in variables: return variables[val]
    value: Value = Value()
    variables[val] = value
    return value

def get_print_value(variables:Dict[str, Value], s:str) -> Union[Value, str]:
    return get_value(variables, s) if s[0] != "\"" else s[1:-1]

def get_arithmetic_operation(tokens: List[str], variables:Dict[str, Value]) -> Arithmetic:
    v1:Value = get_value(variables, tokens[2])
    if len(tokens) == 3: return Constant(v1)

    op:str = tokens[3]
    v2:Value = get_value(variables, tokens[4])
    if op == "+": return Addition(v1, v2)
    if op == "-": return Subtraction(v1, v2)
    if op == "*": return Multiplication(v1, v2)
    return Division(v1, v2)

def get_condition(tokens: List[str], variables:Dict[str, Value]) -> Conditional:
    v1:Value = get_value(variables, tokens[0])
    v2:Value = get_value(variables, tokens[2])
    op:str = tokens[1]
    if op == "<": return LessThan(v1, v2)
    if op == "=": return Equal(v1, v2)
    if op == ">": return GreaterThan(v1, v2)
    if op == "<=": return LessEqual(v1, v2)
    if op == "<>": return NotEqual(v1, v2)
    return GreaterEqual(v1, v2)

def get_cmd(line_num:int, line_dict: Dict[int, Statement], variables:Dict[str, Value], goto_list: List[Statement], cmd:str, args:str) -> Statement:
    if cmd[0] == "P":
        return (PrintLineStatement if cmd[-1] == "N" else PrintStatement)(line_num, get_print_value(variables, args))

    tokens: List[str] =  args.split(" ")
    if cmd[0] == "L":
        return Assignment(
            line_num,
            get_value(variables, tokens[0]),
            get_arithmetic_operation(tokens, variables)
        )
    
    # cmd == 'IF <> THEN GOTO <>'
    if_statement: If = If(line_num, get_condition(tokens, variables), int(tokens[-1]))
    goto_list.append(if_statement)
    return if_statement

def handle_line(lines:Dict[int, Statement], variables:Dict[str, Value], goto_list: List[Statement], line:str) -> None:
    num_str, statement = tuple(line.split(" ", 1))
    line_num: int = int(num_str)
    cmd, args = tuple(statement.split(" ", 1))
    lines[line_num] = get_cmd(line_num, lines, variables, goto_list, cmd, args)

def run(line_dict:Dict[int, Statement], goto_list:List[Statement]) -> None:
    lines: List[Statement] = sorted(line_dict.values(), key= lambda line: line.line_num)
    line_count: int = len(lines)
    for idx in range(1, line_count):
        lines[idx - 1].next = lines[idx]
    for statement in goto_list:
        statement.alt = line_dict[statement.label_num]
    
    curr: Union[Statement, None] = lines[0]
    while curr is not None:
        curr = curr.eval()

def main() -> None:
    #debug_print("Start...")
    lines:Dict[int, Statement] = {}
    variables:Dict[str, Value] = {}
    goto_list: List[Statement] = []

    try:
        while True:
            line: str = input()
            #debug_print("LN:", line)
            if not line: break
            handle_line(lines, variables, goto_list, line)
    except EOFError:
        #debug_print(e)
        pass
    #debug_print("Read:", len(lines), "lines")

    run(lines, goto_list)
    PrintStatement.buffer.append("".join(PrintStatement.line))
    print("\n".join(PrintStatement.buffer), end="")
    
if __name__ == "__main__":
    main()