using System.Collections;
using UnityEngine;
using static UnityEngine.GraphicsBuffer;


public class Enemies : MonoBehaviour
{
    /*
     * 
     * N O T E: This script is still a work in progress.
     * 
     */

    //Variables.
    public bool isDependent;
    public bool isJumping;
    private bool canPeak;
    public bool onHead;
    public bool isCollider;
    public bool isDelay;
    public bool canAttack;

    public float jumpHeight;
    public float peakVelocity;
    public float movementSpeed;
    public float knockBackForce;
    public float hitDelay;
    public float initialHeight;
    public float attackRange;

    public int objectsColliding;

    private Animator anim;
    public AnimationClip jumpAnim;

    private Rigidbody2D rb;

    public GameObject body;
    public GameObject player;
    public GameObject physicalCollider;
    public GameObject triggerCollider;
    public GameObject wholeParent;

    public Sprite onHeadSpriteEyes;
    public Sprite onHeadSpriteMouth;
    public Sprite offHeadSpriteEyes;
    public Sprite offHeadSpriteMouth;
    public Sprite defaultHeadSpriteEyes;
    public Sprite defaultHeadSpriteMouth;

    void Start()
    {
        //Initializes anim and rb.
        anim = GetComponent<Animator>();
        rb = GetComponent<Rigidbody2D>();


        if (isDependent)
        {
            //Sets the first frame of the animation if it is a Dependent enemy.
            SetFirstFrame(jumpAnim);
        }
    }

    // Update is called once per frame
    void Update()
    {
        //Update code for Dependent.
        if (isDependent)
        {
            //Only runs if the enemy is not on the head of the player. This only runs if the enemy is not on the player's head and if it is in range.
            if (onHead != true && Vector2.Distance(transform.position, player.transform.position) < attackRange)
            {
                //If the enemy is on the ground and it cannot attack, it set it to jump up in the air.
                if (canAttack == false && isJumping == false && objectsColliding != 0)
                {

                    canAttack = true;
                    isJumping = true;
                    canPeak = false;

                    //Sets the animation to play.
                    PlayFromPause(jumpAnim);

                    //After a brief pause the enemy jumps.
                    StartCoroutine(Delay());
                }

                //As long as the enemy has a rigidbody (not on head), it will check if it has reached the peak of its jump.
                if (rb != null)
                {
                    if (rb.linearVelocity.y < peakVelocity && canPeak == true && isJumping == true)
                    {
                        //If the enemy has reached hte peak of its jump, it sets the anim to the first frame.
                        SetFirstFrame(jumpAnim);
                    }
                }

                //If the enemy is jumping, it moves towards the player in the air.
                if (isJumping == true && objectsColliding == 0)
                {
                    float newX = Mathf.MoveTowards(transform.position.x, player.transform.position.x, Mathf.Abs(transform.position.x - player.transform.position.x) * movementSpeed * Time.deltaTime);
                    transform.position = new Vector2(newX, transform.position.y);
                }

                //If the enemy is not touching any ground, then it is considered in the air.
                if (objectsColliding != 0)
                {
                    isJumping = false;
                }
                else
                {
                    isJumping = true;
                }
            }

        }
    }

    //Used for delaying the jump to sync with the animation.
    IEnumerator Delay()
    {
        yield return new WaitForSeconds(.2f);

        if (GetComponent<Rigidbody2D>() != null)
        {
            GetComponent<Rigidbody2D>().AddForce(new Vector2(0f, jumpHeight), ForceMode2D.Impulse);

        }

        yield return new WaitForSeconds(.3f);

        canPeak = true;
        canAttack = false;
    }

    private void OnTriggerEnter2D(Collider2D other)
    {
        //If the enemy collider is triggered by the ground or a ground tagged object...
        if (other.gameObject.CompareTag("Ground"))
        {
            if (isDependent != true)
            {
                transform.parent.GetComponent<Enemies>().SetFirstFrame(jumpAnim);
            }
            objectsColliding += 1;
        }

        //If the enemy collider is triggered by the head of the player...
        if (other.gameObject.CompareTag("Head") && isCollider && transform.parent.GetComponent<Enemies>().onHead == false && transform.parent.GetComponent<Enemies>().isDelay == false)
        {
            //Called the a function in the parent to start the process of placing itself on the player's head.
            transform.parent.GetComponent<Enemies>().OnHead(other);
        }

        //If the enemy collider is triggered by a ground object at a high speed...
        if (other.gameObject.GetComponent<Object_Manager>() != null)
        {
            if (other.gameObject.CompareTag("Ground") && isCollider && transform.parent.GetComponent<Enemies>().onHead == true && other.gameObject.GetComponent<Object_Manager>().isGhost == false)
            {
                if (other.GetComponent<Rigidbody2D>() != null && other.GetComponent<Rigidbody2D>().linearVelocity.magnitude * other.GetComponent<Rigidbody2D>().mass > 15)
                {
                    //Starts process of taking the enemy off the head of the player.
                    transform.parent.GetComponent<Enemies>().OffHead(other);
                }
            }
        }

        //Kills the enemy.
        if (other.gameObject.CompareTag("Lava") && isCollider)
        {
            Destroy(wholeParent.gameObject);
        }
    }
    private void OnTriggerExit2D(Collider2D other)
    {
        //If the enemy exits the ground, it detects one less colliding object.
        if (other.gameObject.GetComponent<Object_Manager>() != null)
        {
            if (other.gameObject.CompareTag("Ground") && other.gameObject.GetComponent<Object_Manager>().isGhost == false)
            {
                objectsColliding -= 1;
            }
        }
        else
        {
            if (other.gameObject.CompareTag("Ground"))
            {
                objectsColliding -= 1;
            }
        }
    }

    //Sets the animation to the first frame.
    public void SetFirstFrame(AnimationClip animClip)
    {
        anim.Play(animClip.name, -1, 0f);
        anim.speed = 0;
    }

    //Sets to the last frame.
    public void SetLastFrame(AnimationClip animClip)
    {
        anim.Play(animClip.name, -1, 1f);
        anim.speed = 0;
    }

    //Plays the anim if paused.
    public void PlayFromPause(AnimationClip animClip)
    {
        anim.speed = 1;
        anim.Play(animClip.name);
    }

    //Calls to place the enemy on the head of the player.
    public void OnHead(Collider2D other)
    {
        //Makes the enemy a child of the player.
        transform.parent = other.transform;
        onHead = true;

        //Destroys the rb so that it will not interact with the collider of the player.
        if (transform.GetComponent<Rigidbody2D>() != null)
        {
            Destroy(rb);
        }

        //Sets the anim, changes the collider to a trigger, and slows the player down.
        physicalCollider.transform.GetComponent<BoxCollider2D>().isTrigger = true;
        transform.position = other.transform.position;
        SetFirstFrame(jumpAnim);
        player.GetComponent<Player_Manager>().maxWalkSpeed = player.GetComponent<Player_Manager>().slowWalkSpeed;
        player.GetComponent<Player_Manager>().maxRunSpeed = player.GetComponent<Player_Manager>().slowRunSpeed;

        //Changes the eye and mouth sprites. 
        foreach (Transform x in transform)
        {
            if (x.gameObject.name.Contains("Eye"))
            {
                x.GetComponent<SpriteRenderer>().sprite = onHeadSpriteEyes;
            }
            if (x.gameObject.name.Contains("Mouth"))
            {
                x.GetComponent<SpriteRenderer>().sprite = onHeadSpriteMouth;
            }
        }

        //Decreases the health of the player.
        player.GetComponent<Health>().DecreaseHealth();
    }

    //Called when the enemy is hit with an object and jumps off the player's head.
    void OffHead(Collider2D other)
    {
        transform.parent = null;

        //Sets the trigger collider to false.
        triggerCollider.GetComponent<BoxCollider2D>().enabled = false;

        //Readds the rb.
        if (transform.GetComponent<Rigidbody2D>() == null)
        {
            transform.gameObject.AddComponent<Rigidbody2D>();
        }

        //Re-solidifies the collider, the rotation, and reenstates the player's original speed.
        physicalCollider.transform.GetComponent<BoxCollider2D>().isTrigger = false;
        rb = GetComponent<Rigidbody2D>();
        transform.eulerAngles = new Vector2(0,0);
        rb.constraints = RigidbodyConstraints2D.FreezeRotation;
        player.GetComponent<Player_Manager>().maxWalkSpeed = player.GetComponent<Player_Manager>().savedWalkSpeed;
        player.GetComponent<Player_Manager>().maxRunSpeed = player.GetComponent<Player_Manager>().savedRunSpeed;

        //Resets the player's collision detection to dismiss the enemy's collider.
        if (player.GetComponent<Player_Manager>().groundCount > 0)
        {
            player.GetComponent<Player_Manager>().groundCount -= 1;
        }

        //Adds a knockback force to the enemy.
        if (other.transform.position.x < transform.position.x)
        {
            rb.AddForce(new Vector2(knockBackForce, 0f));
        }
        else
        {
            rb.AddForce(new Vector2(-knockBackForce, 0f));

        }

        //Changes the sprites of the eyes and mouth to express discomfort.
        foreach (Transform x in transform)
        {
            if (x.gameObject.name.Contains("Eye"))
            {
                x.GetComponent<SpriteRenderer>().sprite = offHeadSpriteEyes;
            }
            if (x.gameObject.name.Contains("Mouth"))
            {
                x.GetComponent<SpriteRenderer>().sprite = offHeadSpriteMouth;
            }
        }

        StartCoroutine(HitDelay());
    }

    //Delays so that the enemy cannot attack again immediately.
    IEnumerator HitDelay()
    {
        isDelay = true;
        yield return new WaitForSeconds(hitDelay);
        isDelay = false;
        onHead = false;
        triggerCollider.GetComponent<BoxCollider2D>().enabled = true;

        //Changes the sprites of the eyes and mouth back to normal.
        foreach (Transform x in transform)
        {
            if (x.gameObject.name.Contains("Eye"))
            {
                x.GetComponent<SpriteRenderer>().sprite = defaultHeadSpriteEyes;
            }
            if (x.gameObject.name.Contains("Mouth"))
            {
                x.GetComponent<SpriteRenderer>().sprite = defaultHeadSpriteMouth;
            }
        }
    }
}
