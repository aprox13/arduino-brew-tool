
class delayed_action
{
public:
    delayed_action(long delay);

    void tick(long now);

protected:
    virtual void action(long now) = 0;
    long delay;
private:
    
    long lastExecTime;
};
