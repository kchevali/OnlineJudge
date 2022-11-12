#include <bits/stdc++.h>
#define ARG_COUNT 6
#define VAR_COUNT 26
#define MAX_VAR VAR_COUNT + 'A'

struct Value{
    int value;
    Value(): value(0) {}
    Value(int value): value(value) {}
};

struct BaseExpression {
    Value* a;
    BaseExpression(Value* a): a(a) {}
    virtual int eval() { return a->value; }
};

using ConstantStatement = BaseExpression;

struct OperationStatement: public BaseExpression{
    Value* b;
    OperationStatement(Value* a, Value* b): BaseExpression(a), b(b) {}
};

struct AdditionStatement: public OperationStatement{
    int eval() { return a->value + b->value; }
    AdditionStatement(Value* a, Value* b): OperationStatement(a, b) {}
};

struct SubtractionStatement: public OperationStatement{
    int eval() { return a->value - b->value; }
    SubtractionStatement(Value* a, Value* b): OperationStatement(a, b) {}
};

struct MultiplicationStatement: public OperationStatement{
    int eval() { return a->value * b->value; }
    MultiplicationStatement(Value* a, Value* b): OperationStatement(a, b) {}
};

struct DivisionStatement: public OperationStatement{
    int eval() { return a->value / b->value; }
    DivisionStatement(Value* a, Value* b): OperationStatement(a, b) {}
};

struct EqualStatement: public OperationStatement{
    int eval() { return a->value == b->value; }
    EqualStatement(Value* a, Value* b): OperationStatement(a, b) {}
};

struct GreaterThanStatement: public OperationStatement{
    int eval() { return a->value > b->value; }
    GreaterThanStatement(Value* a, Value* b): OperationStatement(a, b) {}
};

struct LessThanStatement: public OperationStatement{
    int eval() { return a->value < b->value; }
    LessThanStatement(Value* a, Value* b): OperationStatement(a, b) {}
};

struct NotEqualStatement: public OperationStatement{
    int eval() { return a->value != b->value; }
    NotEqualStatement(Value* a, Value* b): OperationStatement(a, b) {}
};

struct LessEqualStatement: public OperationStatement{
    int eval() { return a->value <= b->value; }
    LessEqualStatement(Value* a, Value* b): OperationStatement(a, b) {}
};

struct GreaterEqualStatement: public OperationStatement{
    int eval() { return a->value >= b->value; }
    GreaterEqualStatement(Value* a, Value* b): OperationStatement(a, b) {}
};

struct PrintValue {
    virtual std::string eval() = 0;
};

struct StringConstant: public PrintValue {
    std::string s;
    StringConstant(std::string s): s(s) {}
    std::string eval(){ return s; }
};

struct PrintVariable: public PrintValue {
    Value* value;
    PrintVariable(Value* value): value(value) {}
    std::string eval(){ return std::to_string(value->value); }
};

struct Statement {
    Statement* next = nullptr;
    virtual Statement* execute() = 0;
};

struct PrintStatement: public Statement {
    PrintValue* value;
    PrintStatement(PrintValue* value): value(value) {}
    Statement* execute(){ std::cout << value->eval(); return next; }
};

struct PrintlnStatement: public Statement {
    PrintValue* value;
    PrintlnStatement(PrintValue* value): value(value) {}
    Statement* execute(){ std::cout << value->eval() << std::endl; return next; }
};

struct AssignmentStatement: public Statement {
    Value* variable;
    BaseExpression* statement;
    AssignmentStatement(Value* variable, BaseExpression* statement): variable(variable), statement(statement){}
    Statement* execute(){  variable->value = statement->eval(); return next; }
};

struct IfGoToStatement: public Statement {
    OperationStatement* condition = nullptr;
    Statement* alt_next = nullptr;
    int alt_line_num;
    IfGoToStatement(OperationStatement* condition, int alt_line_num): condition(condition), alt_line_num(alt_line_num) {}
    Statement* execute(){ return condition->eval() ? alt_next : next; }
};

struct Line {
    int line_num;
    Statement* statement;
    Line(int line_num, Statement* statement): line_num(line_num), statement(statement) {}
};

inline Value* get_int_value(Value* value_arr[MAX_VAR], const std::string& v){
    return v[0] >= 'A' ? value_arr[v[0]] : new Value(std::stoi(v));
}

inline BaseExpression* get_arithmetic_operation(Value* value_arr[MAX_VAR], std::string tokens[ARG_COUNT], int arg_count){
    Value *a = get_int_value(value_arr, tokens[2]);
    if (arg_count == 3) return new ConstantStatement(a);

    Value *b = get_int_value(value_arr, tokens[4]);
    switch(tokens[3][0]){
        case '+': return new AdditionStatement(a, b);
        case '-': return new SubtractionStatement(a, b);
        case '*': return new MultiplicationStatement(a, b);
        default: return new DivisionStatement(a, b);
    }
}

inline OperationStatement* get_condition(Value* value_arr[MAX_VAR], std::string tokens[ARG_COUNT], int arg_count){
    Value *a = get_int_value(value_arr, tokens[0]), *b = get_int_value(value_arr, tokens[2]);
    if(tokens[1] == "=") return new EqualStatement(a, b);
    if(tokens[1] == "<") return new LessThanStatement(a, b);
    if(tokens[1] == ">") return new GreaterThanStatement(a, b);
    if(tokens[1] == "<=") return new LessEqualStatement(a, b);
    if(tokens[1] == ">=") return new GreaterEqualStatement(a, b);
    return new NotEqualStatement(a, b);
}

Statement* get_statement(Value* value_arr[MAX_VAR], int line_num, const std::string& cmd, const std::string& line, std::vector<IfGoToStatement*>& if_statements){
    if(cmd[0] == 'P'){
        PrintValue* pValue = line[1] == '"' ?
            (PrintValue*) new StringConstant(line.substr(2, line.length() - 3)):
            (PrintValue*) new PrintVariable(value_arr[line[1]]);
        return cmd[cmd.length() - 1] == 'N' ?
            (Statement*) new PrintlnStatement(pValue) :
            (Statement*) new PrintStatement(pValue);
    }

    std::istringstream ss(line);
    std::string token;
    std::string tokens[ARG_COUNT];
    int arg_count = 0;
    while(ss >> token) tokens[arg_count++] = token;

    switch(cmd[0]){
        case 'L':
            return new AssignmentStatement(
                value_arr[tokens[0][0]],
                get_arithmetic_operation(value_arr, tokens, arg_count)
            );
        default:
            auto if_statement = new IfGoToStatement(
                get_condition(value_arr, tokens, arg_count),
                std::stoi(tokens[arg_count - 1])
            );
            if_statements.push_back(if_statement);
            return if_statement;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    Value* value_arr[MAX_VAR];
    for(int i = 0; i < VAR_COUNT; i++) value_arr[i + 'A'] = new Value();

    int line_num;
    std::string cmd, line, args[10];
    std::vector<Line*> lines;
    std::vector<IfGoToStatement*> if_statements;
    std::unordered_map<int, Statement*> line_map;
    while(std::cin >> line_num >> cmd){
        std::getline(std::cin, line);
        auto statement = get_statement(value_arr, line_num, cmd, line, if_statements);
        lines.push_back(new Line(line_num, statement));
        line_map[line_num] = statement;
    }
    if(lines.size() == 0) return 0;

    std::sort(lines.begin(), lines.end(), [](const Line* a, const Line* b) {
        return a->line_num < b->line_num;
    });

    line_map[lines[0]->line_num] = lines[0]->statement;
    for(int i = 1; i < lines.size(); i++){
        lines[i-1]->statement->next = lines[i]->statement;
    }
    for(const auto if_statement: if_statements){
        if_statement->alt_next = line_map[if_statement->alt_line_num];
    }

    auto pc = lines[0]->statement;
    while(pc != nullptr){
        pc = pc->execute();
    }
}
