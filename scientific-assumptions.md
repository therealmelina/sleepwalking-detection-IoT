# Scientific Assumptions & Project Documentation

## 1. Basic Scientific Assumptions

| Hypothesis | Relevant Explanation |
|---|---|
| Sleepwalking is characterized by involuntary movements. | These movements, unlike normal movements during sleep (such as rolling over), are continuous and last more than a few seconds. |
| Changes in body angle can be detected with an accelerometer. | By installing an MPU6050 sensor on the wrist or waist, deviation from the horizontal or vertical position can be measured. |
| Unlike a sudden alarm, gradual sensory stimulation does not activate the fight-or-flight (sympathetic) response. | Gentle awakening (vibration or low-intensity sound) does not cause stress, and the person wakes up calmly. |
| According to polysomnography studies, sleepwalking lasts at least 10–30 seconds. People also change position every 15–20 minutes during sleep, and these movements usually last less than 5 seconds. (University of Ottawa, Oxford Academic, Mount Sinai Hospital) | Sleepwalking movements usually last more than 10 seconds, but normal movements last less than 5 seconds. |

## 2. Physical Formulas and Mathematical Equations

### 2.1 Body Angle Deviation (relative to vertical)

$$
\theta = \arctan\left(\frac{a_y}{a_z}\right) \times \frac{180}{\pi}
$$

### 2.2 Sleepwalking Detection Conditions

1. Abnormal movement detection:

$$
|\theta - \theta_0| > \theta_{th}
$$

2. Time threshold:

$$
\Delta t_{move} > T_{th}
$$

### 2.3 Moving Average Filter (Noise Removal)

$$
\bar{\theta}_n = \frac{1}{N} \sum_{k=0}^{N-1} \theta_{n-k}
$$

### 2.4 Gradual Awakening State

$$
I(t) =
\begin{cases}
I_1 & \text{if } T_1 \le \Delta t < T_2 \\
I_2 & \text{if } T_2 \le \Delta t < T_3 \\
I_3 & \text{if } \Delta t \ge T_3
\end{cases}
$$

With:

- $T_1 = 10\,s,\quad T_2 = 15\,s,\quad T_3 = 20\,s$
- $I_1 = 30\%\ \text{PWM},\quad I_2 = 70\%\ \text{PWM},\quad I_3 = 100\%\ \text{PWM}$

## 3. Bill of Materials (Components & Costs)

| Part | Qty | Approx. Price (Toman) | Description |
|---|---|---|---|
| Arduino Nano | 1 | 390,000 | Programming and control |
| MPU6050 | 1 | 480,000 | Motion detection |
| Battery charging module | 1 | 168,000 | Reused module |
| mini DFPlayer | 1 | 204,000 | Audio playback module |
| Micro SD card | 1 | 700,000 | Storing selected audio |
| Battery | 1 | 399,000 | Portable power source |
| Speaker (8 Ω) | 1 | 360,000 | Playing selected audio |
| Coin vibration motor | 1 | 50,000 | Generating vibration |

## 4. Sources Consulted

| Question | Answer |
|---|---|
| What sources were used for unknown details? (Books, internet, supervising professor, etc.) | Consultation with the biology teacher and medical students; internet and reliable sources; documentation. |

## 5. Method Comparison

| Method | Advantages | Disadvantages | Cost (Toman) |
|---|---|---|---|
| Chemical drugs | Reduces sleepwalking | Side effects; requires prescription | High |
| Human care | No cost | Negligence, caregiver fatigue | Free |
| Smartwatch | Effective | Expensive; needs charging | ≥ 5,000,000 |
| **Our device** | Higher motion sensitivity; gradual, calm awakening | Needs charging | < 2,000,000 |

## 6. Vibration & Sound Intensity

| | Stage 1 | Stage 2 | Stage 3 |
|---|---|---|---|
| Sound | 10 | 50 | 90 |
| Vibration | 30 | 70 | 100 |

> Scale: 0–100. The original document included a bar chart for these values.
