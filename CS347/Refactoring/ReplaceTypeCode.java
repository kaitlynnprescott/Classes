
class Employee {
    private int _type;               //  the "type code" field
    ... other instance variables ...

    static final int ENGINEER = 0;
    static final int SALESMAN = 1;
    static final int MANAGER = 2;

    Employee(int type) {
        _type = type;
    }

    /*  method with a conditional that behaves differently based on _type  */
    double payAmount() {
        switch (_type) {
            case ENGINEER:
	            return _monthlySalary;
            case SALESMAN:
	            return _monthlySalary + _commission;
            case MANAGER:
	            return _monthlySalary + _bonus;
            default:
	            throw new IllegalArgumentException("unknown employee type");
        }
    }
}
