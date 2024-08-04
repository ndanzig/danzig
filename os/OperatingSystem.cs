using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ProcessScheduling
{
    public class OperatingSystem
    {
        #region List Of Processes for Execution

        private List<Process> listOfProcesses;

        public List<Process> ListOfProcesses
        {
            get { return listOfProcesses; }
            set { listOfProcesses = value; }
        }

        #endregion

        #region Ready Queue used For Execution

        private LinkedList<Process> readyQueue;

        public LinkedList<Process> ReadyQueue
        {
            get { return readyQueue; }
            set { readyQueue = value; }
        }

        #endregion

        #region Process In Execution

        private Process runningProcess;

        public Process RunningProcess
        {
            get { return runningProcess; }
            set { runningProcess = value; }
        }

        #endregion

        #region TimeQuantum Used For RR Algorithm

        private uint timeQuant;

        public uint TimeQuant
        {
            get { return timeQuant; }
            set {
                if (value >= 1 && value <= 100)
                    timeQuant = value;
                else
                    throw new ArgumentException("The time quantum cannot be modified by a wrong value");
            }
        }

        #endregion

        #region Constructor

        public OperatingSystem(List<Process> procList,uint timeQuant)
        {
            listOfProcesses = procList;
            this.timeQuant = timeQuant;
            readyQueue = null;
            runningProcess = null;
        }

        #endregion

        #region Average Waiting Time For Each Algorithm

        private decimal averFCFS;

        public decimal AverFCFS
        {
            get { return averFCFS; }
            set { averFCFS = value; }
        }
        private decimal averSJF;

        public decimal AverSJF
        {
            get { return averSJF; }
            set { averSJF = value; }
        }
        private decimal averPriority;

        public decimal AverPriority
        {
            get { return averPriority; }
            set { averPriority = value; }
        }
        private decimal averRR;

        public decimal AverRR
        {
            get { return averRR; }
            set { averRR = value; }
        }

        #endregion

        #region SJF Scheduling

        public void SJFScheduling()
        {
            uint timeCounter = 0;
            uint startTimeRunnProcess = 0;
            uint processCounter = 0;

           
            
            readyQueue = new LinkedList<Process>();

            List<RunInterval> execIntervals = new List<RunInterval>();

            

            while (readyQueue.Count != 0 || runningProcess != null || processCounter < listOfProcesses.Count)
            {
                //if a process arrives at this time(timeCounter), enqueue it into the ready queue
                //and remove it from the list
                foreach (Process p in listOfProcesses)
                {
                    if (p.ArrivalTime == timeCounter)
                    {
                        readyQueue.AddLast(p);
                        ++processCounter;
                    }
                }

                //checks if the processor is free
                if (runningProcess == null)
                {
                    if (readyQueue.Count != 0)
                    {
                        uint minimum = readyQueue.Min(p => p.TimeLeft);
                        foreach (Process p in readyQueue)
                        {
                            if (p.TimeLeft == minimum)
                            {
                                runningProcess = p;
                                readyQueue.Remove(p);
                                break;
                            }
                        }
                        startTimeRunnProcess = timeCounter;
                    }
                }
                else
                {
                    if (readyQueue.Count != 0)
                    {
                        uint minimum = readyQueue.Min(p => p.TimeLeft);
                        if (minimum < runningProcess.TimeLeft)
                        {
                            foreach (Process p in readyQueue)
                            {
                                if (p.TimeLeft == minimum)
                                {
                                    execIntervals.Add(new RunInterval(runningProcess.Pid, startTimeRunnProcess, timeCounter));
                                    readyQueue.AddLast(runningProcess);
                                    runningProcess = p;
                                    readyQueue.Remove(p);
                                    break;
                                }
                            }
                            startTimeRunnProcess = timeCounter;
                        }
                    }
                }

                //
                //
                // 1 unit of time
                //
                //

                //add 1 to the time counter
                ++timeCounter;

                //if a process is on execution
                if (runningProcess != null)
                {
                    //substract 1 to the time left of the running process
                    --runningProcess.TimeLeft;
                    //if the running process is finished,delete it
                    if (runningProcess.TimeLeft == 0)
                    {
                        //save the finished process state to the result string
                        execIntervals.Add(new RunInterval(runningProcess.Pid, startTimeRunnProcess, timeCounter));

                        //delete the finished process from the processor
                        runningProcess = null;
                    }
                }
            }

            //deallocate memory
            readyQueue = null;
            runningProcess = null;

            //initialize the field ExecIntervalsSJF of each process
            foreach (RunInterval interv in execIntervals)
            {
                foreach (Process p in listOfProcesses)
                {
                    if (interv.ProcessId == p.Pid)
                        p.ExecIntervalsSJF.Add(interv);
                }
            }

            //initialize the field time left of each process
            foreach (Process p in listOfProcesses)
                p.TimeLeft = p.BurstTime;

            //initialize the field waiting time SJF of each process
            foreach (Process p in listOfProcesses)
            {
                p.WaitingTimeSJF = p.ExecIntervalsSJF[0].WorkBegin - p.ArrivalTime;
                for (int i = 0; i < p.ExecIntervalsSJF.Count - 1; ++i)
                {
                    p.WaitingTimeSJF += p.ExecIntervalsSJF[i + 1].WorkBegin - p.ExecIntervalsSJF[i].WorkEnd;
                }
            }

            //initialize the average waiting time field
            uint totalWT = 0;
            foreach (Process p in listOfProcesses)
            {
                totalWT += p.WaitingTimeSJF;
            }
            this.averSJF = (decimal)totalWT / listOfProcesses.Count;
        }

        #endregion

        #region FCFS Scheduling

        public void FCFSScheduling()
        {
            uint timeCounter = 0;
            uint startTimeRunnProcess=0;
            uint processCounter = 0;


            readyQueue = new LinkedList<Process>();

            List<RunInterval> execIntervals = new List<RunInterval>();

            while (readyQueue.Count!=0 || runningProcess!=null || processCounter<listOfProcesses.Count)
            {
                //if a process arrives at this time(timeCounter), enqueue it into the ready queue
                //and remove it from the list
                foreach (Process p in listOfProcesses)
                {
                    if (p.ArrivalTime == timeCounter)
                    {
                        readyQueue.AddLast(p);
                        ++processCounter;
                    }
                }

                //checks if the processor is free
                if (runningProcess == null)
                {
                    if (readyQueue.Count != 0)
                    {
                        runningProcess = readyQueue.First.Value;
                        readyQueue.RemoveFirst();
                        startTimeRunnProcess = timeCounter;
                    }
                }

                //
                //
                    // 1 unit of time
                //
                //

                //add 1 to the time counter
                ++timeCounter;

                //if a process is on execution
                if (runningProcess != null)
                {
                    //substract 1 to the time left of the running process
                    --runningProcess.TimeLeft;
                    //if the running process is finished,delete it
                    if (runningProcess.TimeLeft == 0)
                    {
                        //save the finished process state to the result string
                        execIntervals.Add(new RunInterval(runningProcess.Pid, startTimeRunnProcess, timeCounter));

                        //initialize the waiting time field of the finished process
                        runningProcess.WaitingTimeFCFS = startTimeRunnProcess - runningProcess.ArrivalTime;

                        //delete the finished process from the processor
                        runningProcess = null;
                    }
                }

            }

            //deallocate memory
            readyQueue = null;
            runningProcess = null;

            //initialize the field ExecIntervalsFCFS of each process
            foreach (RunInterval interv in execIntervals)
            {
                foreach (Process p in listOfProcesses)
                {
                    if (interv.ProcessId == p.Pid)
                        p.ExecIntervalsFCFS.Add(interv);
                }
            }

            //initialize the field time left of each process
            foreach (Process p in listOfProcesses)
                p.TimeLeft = p.BurstTime;

            //initialize the average waiting time field
            uint totalWT = 0;
            foreach (Process p in listOfProcesses)
            {
                totalWT += p.WaitingTimeFCFS;
            }
            this.averFCFS = (decimal)totalWT / listOfProcesses.Count;
        }

        #endregion

        #region Priority Scheduling

        public void PriorityScheduling()
        {
            uint timeCounter = 0;
            uint startTimeRunnProcess = 0;
            uint processCounter = 0;



            readyQueue = new LinkedList<Process>();

            List<RunInterval> execIntervals = new List<RunInterval>();



            while (readyQueue.Count != 0 || runningProcess != null || processCounter < listOfProcesses.Count)
            {
                //if a process arrives at this time(timeCounter), enqueue it into the ready queue
                //and remove it from the list
                foreach (Process p in listOfProcesses)
                {
                    if (p.ArrivalTime == timeCounter)
                    {
                        readyQueue.AddLast(p);
                        ++processCounter;
                    }
                }

                //checks if the processor is free
                if (runningProcess == null)
                {
                    if (readyQueue.Count != 0)
                    {
                        uint bigPrior = readyQueue.Min(p => p.Priority);
                        foreach (Process p in readyQueue)
                        {
                            if (p.Priority == bigPrior)
                            {
                                runningProcess = p;
                                readyQueue.Remove(p);
                                break;
                            }
                        }
                        startTimeRunnProcess = timeCounter;
                    }
                }
                else
                {
                    if (readyQueue.Count != 0)
                    {
                        uint bigPrior = readyQueue.Min(p => p.Priority);
                        if (bigPrior < runningProcess.Priority)
                        {
                            foreach (Process p in readyQueue)
                            {
                                if (p.Priority == bigPrior)
                                {
                                    execIntervals.Add(new RunInterval(runningProcess.Pid, startTimeRunnProcess, timeCounter));
                                    readyQueue.AddLast(runningProcess);
                                    runningProcess = p;
                                    readyQueue.Remove(p);
                                    break;
                                }
                            }
                            startTimeRunnProcess = timeCounter;
                        }
                    }
                }

                //
                //
                // 1 unit of time
                //
                //

                //add 1 to the time counter
                ++timeCounter;

                //if a process is on execution
                if (runningProcess != null)
                {
                    //substract 1 to the time left of the running process
                    --runningProcess.TimeLeft;
                    //if the running process is finished,delete it
                    if (runningProcess.TimeLeft == 0)
                    {
                        //save the finished process state to the result string
                        execIntervals.Add(new RunInterval(runningProcess.Pid, startTimeRunnProcess, timeCounter));

                        //delete the finished process from the processor
                        runningProcess = null;
                    }
                }
            }

            //deallocate memory
            readyQueue = null;
            runningProcess = null;

            //initialize the field ExecIntervalsPriority of each process
            foreach (RunInterval interv in execIntervals)
            {
                foreach (Process p in listOfProcesses)
                {
                    if (interv.ProcessId == p.Pid)
                        p.ExecIntervalsPriority.Add(interv);
                }
            }

            //initialize the field time left of each process
            foreach (Process p in listOfProcesses)
                p.TimeLeft = p.BurstTime;

            //initialize the field waiting time Priority of each process
            foreach (Process p in listOfProcesses)
            {
                p.WaitingTimePriority = p.ExecIntervalsPriority[0].WorkBegin - p.ArrivalTime;
                for (int i = 0; i < p.ExecIntervalsPriority.Count - 1; ++i)
                {
                    p.WaitingTimePriority += p.ExecIntervalsPriority[i + 1].WorkBegin - p.ExecIntervalsPriority[i].WorkEnd;
                }
            }

            //initialize the average waiting time field
            uint totalWT = 0;
            foreach (Process p in listOfProcesses)
            {
                totalWT += p.WaitingTimePriority;
            }
            this.averPriority = (decimal)totalWT / listOfProcesses.Count;
        }

        #endregion

        #region RR Scheduling

        public void RRScheduling()
        {
            uint timeCounter = 0;
            uint currTimeQuantum = 0;

            uint startTimeRunnProcess = 0;
            uint processCounter = 0;



            readyQueue = new LinkedList<Process>();

            List<RunInterval> execIntervals = new List<RunInterval>();

            while (readyQueue.Count != 0 || runningProcess != null || processCounter < listOfProcesses.Count)
            {
                //if a process arrives at this time(timeCounter), enqueue it into the ready queue
                //and remove it from the list
                foreach (Process p in listOfProcesses)
                {
                    if (p.ArrivalTime == timeCounter)
                    {
                        readyQueue.AddLast(p);
                        ++processCounter;
                    }
                }

                //checks if the processor is free
                if (runningProcess == null)
                {
                    if (readyQueue.Count != 0)
                    {
                        runningProcess = readyQueue.First.Value;
                        currTimeQuantum = 0;
                        readyQueue.RemoveFirst();
                        startTimeRunnProcess = timeCounter;
                    }
                }

                //
                //
                // 1 unit of time
                //
                //

                //add 1 to the time counters
                ++timeCounter;
                ++currTimeQuantum;

                //if a process is on execution
                if (runningProcess != null)
                {
                    //substract 1 to the time left of the running process
                    --runningProcess.TimeLeft;
                    //if the running process is finished,delete it
                    if (runningProcess.TimeLeft == 0)
                    {
                        //save the finished process state to the result string
                        execIntervals.Add(new RunInterval(runningProcess.Pid, startTimeRunnProcess, timeCounter));

                        //delete the finished process from the processor
                        runningProcess = null;

                        //initialize the field currTimeQuant
                        currTimeQuantum = 0;
                    }
                    else
                    {
                        if (currTimeQuantum == this.timeQuant)
                        {
                            //save the paused process state to the result list
                            execIntervals.Add(new RunInterval(runningProcess.Pid, startTimeRunnProcess, timeCounter));
                            //put the paused process at the tail of the ready queue
                            readyQueue.AddLast(runningProcess);
                            //free the processor
                            runningProcess = null;
                        }
                    }
                }

            }

            //deallocate memory
            readyQueue = null;
            runningProcess = null;

            //initialize the field ExecIntervalsRR of each process
            foreach (RunInterval interv in execIntervals)
            {
                foreach (Process p in listOfProcesses)
                {
                    if (interv.ProcessId == p.Pid)
                        p.ExecIntervalsRR.Add(interv);
                }
            }

            //initialize the field time left of each process
            foreach (Process p in listOfProcesses)
                p.TimeLeft = p.BurstTime;

            //initialize the field waiting time RR of each process
            foreach (Process p in listOfProcesses)
            {
                p.WaitingTimeRR = p.ExecIntervalsRR[0].WorkBegin - p.ArrivalTime;
                for (int i = 0; i < p.ExecIntervalsRR.Count - 1; ++i)
                {
                    p.WaitingTimeRR += p.ExecIntervalsRR[i + 1].WorkBegin - p.ExecIntervalsRR[i].WorkEnd;
                }
            }

            //initialize the average waiting time field
            uint totalWT = 0;
            foreach (Process p in listOfProcesses)
            {
                totalWT += p.WaitingTimeRR;
            }
            this.averRR = (decimal)totalWT / listOfProcesses.Count;
        }

        #endregion

        #region Help Functions

        public static Process MinBurstTime(Queue<Process> queue)
        {
            Process minBurstTimeProc = null;

            foreach (Process p in queue)
            {
                if (minBurstTimeProc == null)
                {
                    minBurstTimeProc = p;
                }
                else
                {
                    if (p.BurstTime < minBurstTimeProc.BurstTime)
                        minBurstTimeProc = p;
                }
            }

            
            return minBurstTimeProc;
        }

        public static Process MinPriority(Queue<Process> queue)
        {
            Process minPriorityProc = null;

            foreach (Process p in queue)
            {
                if (minPriorityProc == null)
                {
                    minPriorityProc = p;
                }
                else
                {
                    if (p.Priority < minPriorityProc.Priority)
                        minPriorityProc = p;
                }
            }

            return minPriorityProc;
        }

        #endregion
    }
}
